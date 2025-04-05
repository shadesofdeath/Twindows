#define _CRT_SECURE_NO_WARNINGS
#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <algorithm> // std::transform için
#include <ShellScalingApi.h> // For DPI awareness
#include <windows.h>         // For Windows API
#include <winreg.h>          // For registry access
#include <winsvc.h>          // For service management
#include <shellapi.h>        // For ShellExecute
#include <fstream>           // Dosya işlemleri için
#include <sstream>           // String manipülasyonu için
#include <map>               // Map için eklendi
#include <memory>            // Akıllı işaretçiler için
#include <psapi.h>           // Bellek bilgileri ve RAM yönetimi için
#include <stdexcept>         // Standart exception sınıfları için
#include <thread> // Thread desteği için
#include <chrono> // Zaman işlemleri için

// Güvenli bellek yönetimi için CRT fonksiyonlarını aktifleştir
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Dil yönetim sistemini dahil et
#include "include/languages/languages.h"

// Global dil yöneticisi
LanguageManager g_langManager;

// Bellek optimizasyonu için bayraklar
bool g_memOptimizationEnabled = true;

// Global değişkenler
int themeOption = 0; // Tema tercihi - 0: Sistem teması, 1: Koyu tema, 2: Açık tema

// Bellek kullanımını yönetmek için yardımcı fonksiyonlar
namespace MemoryManager {
    // Bellek sınırlama hedefi (MB cinsinden)
    size_t g_memoryLimitMB = 50; // Varsayılan 50MB limit
    
    // Son temizleme zamanı
    ULONGLONG g_lastCleanupTime = 0;
    
    // Şu anki bellek kullanımını ölç (KB cinsinden)
    size_t GetCurrentMemoryUsage() {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            return static_cast<size_t>(pmc.WorkingSetSize / 1024); // KB cinsinden
        }
        return 0;
    }
    
    // Bellek sınırını kontrol et ve gerekirse optimize et
    void CheckAndOptimizeMemory() {
        if (!g_memOptimizationEnabled) return;
        
        ULONGLONG currentTime = GetTickCount64();
        // Her 5 saniyede bir bellek durumunu kontrol et (çok sık yapılmamalı)
        if (currentTime - g_lastCleanupTime < 5000) return;
        
        size_t currentUsageKB = GetCurrentMemoryUsage();
        size_t limitKB = g_memoryLimitMB * 1024;
        
        // Bellek kullanımı limiti aşıyorsa optimizasyon yap
        if (currentUsageKB > limitKB) {
            // 1. Kullanılmayan belleği sistem havuzuna iade et
            EmptyWorkingSet(GetCurrentProcess());
            
            // 2. Windows'un bellek kullanımını azaltmasını iste
            SetProcessWorkingSetSize(GetCurrentProcess(), static_cast<SIZE_T>(-1), static_cast<SIZE_T>(-1));
            
            g_lastCleanupTime = currentTime;
        }
    }
    
    // Bellek sınırını ayarla
    void SetMemoryLimit(size_t limitMB) {
        g_memoryLimitMB = limitMB;
    }
    
    // Heap fragemantasyonunu azalt
    void CompactHeap() {
        if (!g_memOptimizationEnabled) return;
        
        // Sistem heap'ini kompakt hale getir
        HeapCompact(GetProcessHeap(), 0);
    }
}

// Türkçe karakterleri ASCII eşdeğerlerine dönüştüren fonksiyon
inline std::string TurkishToASCII(const std::string& str) {
    if (str.empty()) return str; // Boş string kontrolü
    
    // Performans için sonuç string'i önceden boyutlandır
    std::string result;
    result.reserve(str.size()); // Bellek fragmentasyonunu azaltmak için baştan rezerve et
    
    // Tek geçişte karakter dönüşümü - daha verimli
    static const std::map<std::string, char> turkishToAscii = {
        {"ç", 'c'}, {"Ç", 'C'},
        {"ğ", 'g'}, {"Ğ", 'G'},
        {"ı", 'i'}, {"İ", 'I'},
        {"ö", 'o'}, {"Ö", 'O'},
        {"ş", 's'}, {"Ş", 'S'},
        {"ü", 'u'}, {"Ü", 'U'}
    };
    
    for (size_t i = 0; i < str.size(); ) {
        // UTF-8 karakter tespiti - ilk byte 0xC4 veya 0xC5 ise Türkçe karakter olabilir
        bool handled = false;
        if (i + 1 < str.size()) {
            // İki baytlık bir karakter dizisini kontrol et
            std::string twoBytes = str.substr(i, 2);
            auto it = turkishToAscii.find(twoBytes);
            if (it != turkishToAscii.end()) {
                result += it->second;
                i += 2; // İki byte atla
                handled = true;
            }
        }
        
        if (!handled) {
            // Normal ASCII karakter
            result += str[i++];
        }
    }
    
    return result;
}

// Kısaltma fonksiyonu - çeviri için
inline std::string T(const std::string& key) {
    std::string translation = g_langManager.Translate(key);
    
    // Mevcut dili al
    std::string currentLanguage = g_langManager.GetCurrentLanguage();
    
    // Türkçe karakterleri ASCII eşdeğerleriyle değiştir
    if (currentLanguage == "tr") {
        return TurkishToASCII(translation);
    }
    
    return translation;
}

// T() fonksiyonunun bir const char* sonucunu doğrudan döndüren versiyonu
// Bu, uyarıları önlemek için kullanılır
inline const char* TC(const std::string& key) {
    static std::string result;
    result = T(key);
    return result.c_str();
}

// Tab içerikleri için tweakleri içeren dosyaları dahil et
#include "include/privacy_tweaks.h"
#include "include/performance_tweaks.h"
#include "include/appearance_tweaks.h"
#include "include/security_tweaks.h"
#include "include/appx_packages.h" // AppX paketleri için
#include "include/windows_utils.h" // Yeni eklediğimiz Windows API işlevleri

// Data structure to hold tweak information
struct Tweak {
    std::string name;
    bool enabled;
    std::string tooltip;
};

// Başlangıçta boş tweakler tanımlanıyor, gerçek durumları LoadSettings() ile yüklenecek
std::vector<PrivacyTweak> privacyTweaks;
std::vector<PerformanceTweak> performanceTweaks;
std::vector<AppearanceTweak> appearanceTweaks;
std::vector<SecurityTweak> securityTweaks;
std::vector<AppXPackage> appxPackages;

// Global değişkenler - başlık çubuğu yüksekliği
const int TITLEBAR_HEIGHT = 40;

// CMD komutlarını gizli çalıştırmak için yardımcı fonksiyon - Eski yöntem
inline bool ExecuteCommandSilent(const char* command) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE; // Pencereyi gizle
    
    ZeroMemory(&pi, sizeof(pi));
    
    // Komutu çalıştır
    if (!CreateProcessA(NULL, (LPSTR)command, NULL, NULL, FALSE, 
                       CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        return false;
    }
    
    // İşlem tamamlanana kadar bekle
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    // İşlem handle'larını kapat
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return true;
}

// Windows'un aksan rengini almak için fonksiyon
ImVec4 GetWindowsAccentColor() {
    DWORD value = 0;
    ImVec4 defaultColor = ImVec4(0.45f, 0.26f, 0.98f, 1.00f); // Varsayılan mor renk
    
    HKEY hKey;
    // Windows aksan rengi için registry anahtarını aç
    if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\DWM"), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        return defaultColor;
    }
    
    DWORD dataSize = sizeof(DWORD);
    bool success = false;
    
    // Önce Windows 10/11 için AccentColor değerini kontrol et
    if (RegQueryValueEx(hKey, TEXT("AccentColor"), 0, NULL, (LPBYTE)&value, &dataSize) == ERROR_SUCCESS) {
        success = true;
    }
    
    // AccentColor bulunamadıysa, ColorPrevalence değerini kontrol et
    if (!success && RegQueryValueEx(hKey, TEXT("ColorPrevalence"), 0, NULL, (LPBYTE)&value, &dataSize) == ERROR_SUCCESS) {
        success = true;
    }
    
    RegCloseKey(hKey);
    
    if (!success) {
        return defaultColor;
    }
    
    // DWORD değeri ABGR formatındadır, bunu RGBA'ya çevir
    float a = ((value >> 24) & 0xFF) / 255.0f;
    float b = ((value >> 16) & 0xFF) / 255.0f;
    float g = ((value >> 8) & 0xFF) / 255.0f;
    float r = (value & 0xFF) / 255.0f;
    
    // Eğer alfa değeri 0 ise, varsayılan 1.0f değerine ayarla
    if (a == 0) a = 1.0f;
    
    return ImVec4(r, g, b, a);
}

// Custom dark theme function with accent color
void ApplyDarkTheme()
{
    try {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // Windows aksan rengini al
        ImVec4 accentColor;
        try {
            accentColor = GetWindowsAccentColor();
        } catch (...) {
            // Aksan rengi alınamazsa varsayılan bir değer kullan
            accentColor = ImVec4(0.45f, 0.26f, 0.98f, 1.00f); // Varsayılan mor renk
        }
        
        // Set style properties
        style.WindowMinSize        = ImVec2(160, 20);
        style.FramePadding         = ImVec2(4, 2);
        style.ItemSpacing          = ImVec2(6, 2);
        style.ItemInnerSpacing     = ImVec2(2, 4);
        style.Alpha                = 0.95f;
        style.WindowRounding       = 8.0f; // Daha belirgin köşe yuvarlaklığı
        style.ChildRounding        = 8.0f; // Çocuk pencere köşelerini de yuvarla
        style.PopupRounding        = 8.0f; // Popup köşelerini de yuvarla
        style.FrameRounding        = 8.0f;
        style.IndentSpacing        = 6.0f;
        style.ColumnsMinSpacing    = 50.0f;
        style.GrabMinSize          = 14.0f;
        style.GrabRounding         = 16.0f;
        style.ScrollbarSize        = 12.0f;
        style.ScrollbarRounding    = 8.0f;
        
        // Set the window title alignment to center
        style.WindowTitleAlign     = ImVec2(0.0f, 0.5f); // Başlığı sola hizala

        // Colors
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.04f, 0.04f, 0.04f, 0.94f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.20f, 0.20f, 0.20f, 0.54f); // Checkbox arka planı - daha belirgin
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.40f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(accentColor.x * 0.7f, accentColor.y * 0.7f, accentColor.z * 0.7f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.40f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.52f);
        colors[ImGuiCol_Button]                 = ImVec4(0.20f, 0.20f, 0.20f, 0.40f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
        colors[ImGuiCol_Header]                 = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.15f, 0.15f, 0.15f, 0.80f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
        colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 0.13f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        
        // Additional colors - check if they exist in the ImGui version
    #ifdef ImGuiCol_Tab
        colors[ImGuiCol_Tab]                    = ImVec4(accentColor.x * 0.6f, accentColor.y * 0.6f, accentColor.z * 0.6f, 0.73f);
        colors[ImGuiCol_TabHovered]             = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.50f);
        colors[ImGuiCol_TabSelected]            = ImVec4(accentColor.x * 0.8f, accentColor.y * 0.8f, accentColor.z * 0.8f, 1.00f);
    #endif

    #ifdef ImGuiCol_TabSelectedOverline
        colors[ImGuiCol_TabSelectedOverline]    = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
    #endif

    #ifdef ImGuiCol_TabDimmed
        colors[ImGuiCol_TabDimmed]              = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
        colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    #endif

    #ifdef ImGuiCol_TabDimmedSelectedOverline
        colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
    #endif

        colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        
    #ifdef ImGuiCol_TableHeaderBg
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    #endif

    #ifdef ImGuiCol_TextLink
        colors[ImGuiCol_TextLink]               = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
    #endif

        colors[ImGuiCol_TextSelectedBg]         = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
        
    #ifdef ImGuiCol_DragDropTarget
        colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    #endif

    #ifdef ImGuiCol_NavCursor
        colors[ImGuiCol_NavCursor]              = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    #endif

    #ifdef ImGuiCol_ModalWindowDimBg
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    #endif
    } catch (const std::exception& e) {
        OutputDebugStringA("ApplyDarkTheme hatası: ");
        OutputDebugStringA(e.what());
        // Hata olursa ImGui varsayılan stilini kullan
        ImGui::StyleColorsDark();
    } catch (...) {
        OutputDebugStringA("ApplyDarkTheme beklenmeyen hata");
        // Hata olursa ImGui varsayılan stilini kullan
        ImGui::StyleColorsDark();
    }
}

// Light tema fonksiyonu ekliyorum
void ApplyLightTheme()
{
    try {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // Windows aksan rengini al
        ImVec4 accentColor;
        try {
            accentColor = GetWindowsAccentColor();
        } catch (...) {
            // Aksan rengi alınamazsa varsayılan bir değer kullan
            accentColor = ImVec4(0.15f, 0.55f, 0.85f, 1.00f); // Varsayılan mavi
        }
        
        // Set style properties
        style.WindowMinSize        = ImVec2(160, 20);
        style.FramePadding         = ImVec2(4, 2);
        style.ItemSpacing          = ImVec2(6, 2);
        style.ItemInnerSpacing     = ImVec2(2, 4);
        style.Alpha                = 0.95f;
        style.WindowRounding       = 8.0f; // Daha belirgin köşe yuvarlaklığı
        style.ChildRounding        = 8.0f; // Çocuk pencere köşelerini de yuvarla
        style.PopupRounding        = 8.0f; // Popup köşelerini de yuvarla
        style.FrameRounding        = 8.0f;
        style.IndentSpacing        = 6.0f;
        style.ColumnsMinSpacing    = 50.0f;
        style.GrabMinSize          = 14.0f;
        style.GrabRounding         = 8.0f;
        style.ScrollbarSize        = 12.0f;
        style.ScrollbarRounding    = 16.0f;
        
        // Set the window title alignment to center
        style.WindowTitleAlign     = ImVec2(0.0f, 0.5f); // Başlığı sola hizala

        // Light Colors
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
        colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.85f, 0.85f, 0.85f, 1.00f); // Checkbox arka planı - daha belirgin
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.40f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.67f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(accentColor.x * 0.8f, accentColor.y * 0.8f, accentColor.z * 0.8f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.40f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.78f);
        colors[ImGuiCol_Button]                 = ImVec4(0.80f, 0.80f, 0.80f, 0.40f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.50f);
        colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.75f, 0.75f, 0.75f, 0.80f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.00f, 0.00f, 0.00f, 0.06f);
        colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.00f, 0.00f, 0.00f, 0.13f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        
    #ifdef ImGuiCol_Tab
        colors[ImGuiCol_Tab]                    = ImVec4(accentColor.x * 0.7f, accentColor.y * 0.7f, accentColor.z * 0.7f, 0.86f);
        colors[ImGuiCol_TabHovered]             = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.80f);
        colors[ImGuiCol_TabSelected]            = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
    #endif

    #ifdef ImGuiCol_TabSelectedOverline
        colors[ImGuiCol_TabSelectedOverline]    = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
    #endif

        colors[ImGuiCol_PlotLines]              = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        
    #ifdef ImGuiCol_TableHeaderBg
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(accentColor.x * 0.7f, accentColor.y * 0.7f, accentColor.z * 0.7f, 1.00f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
    #endif

        colors[ImGuiCol_TextSelectedBg]         = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.35f);
        
    #ifdef ImGuiCol_NavCursor
        colors[ImGuiCol_NavCursor]              = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
    #endif

    #ifdef ImGuiCol_ModalWindowDimBg
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
    #endif
    } catch (const std::exception& e) {
        OutputDebugStringA("ApplyLightTheme hatası: ");
        OutputDebugStringA(e.what());
        // Hata olursa ImGui varsayılan stilini kullan
        ImGui::StyleColorsLight();
    } catch (...) {
        OutputDebugStringA("ApplyLightTheme beklenmeyen hata");
        // Hata olursa ImGui varsayılan stilini kullan
        ImGui::StyleColorsLight();
    }
}

// Windows tema tespiti fonksiyonu
bool IsWindowsInDarkMode()
{
    DWORD value = 0;
    DWORD dataSize = sizeof(DWORD);
    HKEY hKey;
    bool darkMode = false;

    // HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize
    if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hKey, TEXT("AppsUseLightTheme"), 0, NULL, (LPBYTE)&value, &dataSize) == ERROR_SUCCESS)
        {
            darkMode = (value == 0); // 0 = Dark, 1 = Light
        }
        RegCloseKey(hKey);
    }
    
    return darkMode;
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // Pencere sürükleme için değişkenler
    static bool s_isDragging = false;
    static POINT s_lastCursorPos = { 0, 0 };
    
    // Sürükleme dışında ImGui işlemine öncelik ver
    // Bu kapatma butonunun düzgün çalışmasını sağlar
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_LBUTTONDOWN:
        {
            // Sol tıklama basıldığında sürükleme başlat - sadece başlık çubuğu bölgesinde
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ScreenToClient(hWnd, &cursorPos);
            
            // Başlık çubuğunun yüksekliğini kontrol et
            if (cursorPos.y <= TITLEBAR_HEIGHT) {
                // Pencerenin sağ üst köşesindeki kapatma butonu için bir kontrol ekleyelim
                // Ekranın sağ üst tarafındaki 40 piksellik alanda kapatma butonu var
                // Bu alanda sürükleme devre dışı bırakılacak
                int windowWidth = 0;
                {
                    RECT windowRect;
                    GetWindowRect(hWnd, &windowRect);
                    windowWidth = windowRect.right - windowRect.left;
                }
                
                // Sağ üst köşedeki kapatma butonuna yakınsa sürüklemeyi engelle
                if (cursorPos.x < (windowWidth - 40)) {
                    s_isDragging = true;
                    SetCapture(hWnd);
                    GetCursorPos(&s_lastCursorPos);
                }
                return 0; // Başlık çubuğunda tıklandı
            }
            break; // Diğer durumlarda normal işleme devam et
        }
    case WM_MOUSEMOVE:
        {
            // Fare hareket ettiğinde sürükleme devam ediyorsa pencereyi taşı
            if (s_isDragging) {
                POINT currentPos;
                GetCursorPos(&currentPos);
                
                // Pencereyi hareket ettir
                RECT windowRect;
                GetWindowRect(hWnd, &windowRect);
                int newX = windowRect.left + (currentPos.x - s_lastCursorPos.x);
                int newY = windowRect.top + (currentPos.y - s_lastCursorPos.y);
                
                SetWindowPos(hWnd, NULL, newX, newY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
                
                s_lastCursorPos = currentPos;
                return 0; // Sürükleme işlemi tamamlandı
            }
            break; // Sürükleme yoksa normal işleme devam et
        }
    case WM_LBUTTONUP:
        {
            // Sol tıklama bırakıldığında sürüklemeyi sonlandır
            if (s_isDragging) {
                s_isDragging = false;
                ReleaseCapture();
                return 0; // Sürükleme sona erdi mesajı işlendi
            }
            break; // Sürükleme yoksa normal işleme devam et
        }
    case WM_SIZE:
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

// Uygulama ayarlarını yükle
void LoadSettings() {
    try {
        // Başlangıçta aktif tweaks listelerini yükle
        privacyTweaks = GetPrivacyTweaks();
        performanceTweaks = GetPerformanceTweaks();
        appearanceTweaks = GetAppearanceTweaks();
        securityTweaks = GetSecurityTweaks();
        
        // AppX paketlerini yükle
        appxPackages = GetInstalledAppXPackages();
        
        bool languageLoaded = false;
        
        // Try to load language preference from registry
        HKEY hKey;
        if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Twindows", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            char langCode[10];
            DWORD dataSize = sizeof(langCode);
            if (RegQueryValueExA(hKey, "Language", 0, NULL, (LPBYTE)langCode, &dataSize) == ERROR_SUCCESS) {
                std::string language(langCode);
                g_langManager.LoadLanguage(language);
                std::cout << "Loaded language from registry: " << language << std::endl;
                languageLoaded = true;
            }
            RegCloseKey(hKey);
        }
        
        // If registry loading failed, try INI file
        if (!languageLoaded) {
            std::ifstream settingsFile("twindows_settings.ini");
            if (settingsFile.is_open()) {
                std::string line;
                while (std::getline(settingsFile, line)) {
                    // Look for language setting
                    if (line.substr(0, 9) == "language=") {
                        std::string language = line.substr(9);
                        g_langManager.LoadLanguage(language);
                        std::cout << "Loaded language from INI file: " << language << std::endl;
                        
                        // Save to registry for future use
                        if (RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Twindows", 0, NULL, 
                                         REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
                            RegSetValueExA(hKey, "Language", 0, REG_SZ, (BYTE*)language.c_str(), language.length() + 1);
                            RegCloseKey(hKey);
                        }
                        
                        languageLoaded = true;
                        break;
                    }
                }
                settingsFile.close();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in LoadSettings: " << e.what() << std::endl;
    }
}

// Ayarları kaydet
void SaveSettings() {
    try {
        std::string currentLanguage = g_langManager.GetCurrentLanguage();
        
        // Save to INI file
        std::ofstream settingsFile("twindows_settings.ini");
        if (settingsFile.is_open()) {
            try {
                // Dil ayarını kaydet
                settingsFile << "language=" << currentLanguage << std::endl;
            } catch (const std::exception& e) {
                OutputDebugStringA("Ayarları yazarken hata: ");
                OutputDebugStringA(e.what());
                OutputDebugStringA("\n");
            }
            
            settingsFile.close();
        } else {
            OutputDebugStringA("Ayarlar dosyası oluşturulamadı veya açılamadı.\n");
        }
        
        // Save to registry
        HKEY hKey;
        if (RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Twindows", 0, NULL, 
                         REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
            RegSetValueExA(hKey, "Language", 0, REG_SZ, (BYTE*)currentLanguage.c_str(), currentLanguage.length() + 1);
            RegCloseKey(hKey);
        } else {
            OutputDebugStringA("Registry kayıt hatası. Dil ayarı kaydedilemedi.\n");
        }
    } catch (const std::exception& e) {
        OutputDebugStringA("Ayarları kaydetme hatası: ");
        OutputDebugStringA(e.what());
        OutputDebugStringA("\n");
    } catch (...) {
        OutputDebugStringA("Ayarları kaydederken beklenmeyen hata.\n");
    }
}

// Yönetici olarak çalışıp çalışmadığımızı kontrol eden fonksiyon
bool IsRunAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    
    if (AllocateAndInitializeSid(&ntAuthority, 2, 
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 
        0, 0, 0, 0, 0, 0, &adminGroup)) {
        
        if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
            isAdmin = FALSE;
        }
        
        FreeSid(adminGroup);
    }
    
    return isAdmin != 0;
}

// Uygulamayı yönetici olarak yeniden başlatan fonksiyon
bool RestartAsAdmin() {
    wchar_t szPath[MAX_PATH];
    
    if (GetModuleFileNameW(NULL, szPath, ARRAYSIZE(szPath))) {
        // Uygulama yolunu aldık, şimdi yönetici olarak başlatalım
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.lpVerb = L"runas"; // Yönetici olarak çalıştır
        sei.lpFile = szPath;
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;
        
        if (!ShellExecuteExW(&sei)) {
            // Kullanıcı izin vermedi veya başka bir hata oldu
            return false;
        }
        
        // Uygulamayı başarıyla yeniden başlattık, mevcut işlemi kapatalım
        return true;
    }
    
    return false;
}

// Ayarlar sekmesi içeriği
void DrawSettingsTab() {
    ImGui::Text("%s", T("Windows Tweaker - Settings").c_str());
    ImGui::Separator();
    ImGui::Spacing();
    
    // Dil ayarı
    ImGui::Text("%s: %s", T("Language").c_str(), 
               T(g_langManager.GetLanguageDisplayName(g_langManager.GetCurrentLanguage())).c_str());
    
    ImGui::SameLine();
    if (ImGui::Button(T("Change Language").c_str())) {
        ImGui::OpenPopup("language_selector");
    }
    
    ImGui::Spacing();
    ImGui::Spacing();
    
    // Dil seçme popup'ı
    if (ImGui::BeginPopup("language_selector")) {
        ImGui::Text("%s", T("Select Language").c_str());
        ImGui::Separator();
        ImGui::Spacing();
        
        auto languages = g_langManager.GetAvailableLanguages();
        for (const auto& langInfo : languages) {
            if (ImGui::MenuItem(T(langInfo.second).c_str())) {
                g_langManager.LoadLanguage(langInfo.first);
                // Dil değiştirildiğinde ayarları kaydet
                SaveSettings();
            }
        }
        
        ImGui::EndPopup();
    }
}

// Hakkında sekmesi içeriği
void DrawAboutTab() {
    ImGui::Text("%s", T("Windows Tweaker - About").c_str());
    ImGui::Separator();
    ImGui::Spacing();
    
    // Renk değişkenleri
    ImVec4 titleColor = ImVec4(0.2f, 0.6f, 1.0f, 1.0f); // Mavi
    ImVec4 linkColor = ImVec4(0.3f, 0.8f, 0.3f, 1.0f);  // Yeşil
    ImVec4 textColor = ImGui::GetStyle().Colors[ImGuiCol_Text]; // Mevcut metin rengi
    
    // Logo veya başlık bölümü
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]); // Daha büyük font
    ImGui::PushStyleColor(ImGuiCol_Text, titleColor);
    ImGui::TextWrapped("Twindows");
    ImGui::PopStyleColor();
    ImGui::PopFont();
    
    ImGui::Spacing();
    ImGui::TextWrapped("%s", T("A comprehensive Windows 11 optimization and tweaking tool").c_str());
    ImGui::Spacing();
    ImGui::Separator();
    
    // Geliştirici bilgisi
    ImGui::TextWrapped("%s: Berkay AY", T("Developer").c_str());
    ImGui::Spacing();
    
    // GitHub bağlantısı
    ImGui::PushStyleColor(ImGuiCol_Text, linkColor);
    ImGui::TextWrapped("GitHub: https://github.com/shadesofdeath/Twindows");
    if (ImGui::IsItemClicked()) {
        ShellExecuteA(NULL, "open", "https://github.com/shadesofdeath/Twindows", NULL, NULL, SW_SHOWNORMAL);
    }
    ImGui::PopStyleColor();
    
    // Ko-fi bağlantısı
    ImGui::PushStyleColor(ImGuiCol_Text, linkColor);
    ImGui::TextWrapped("Ko-fi: https://ko-fi.com/shadesofdeath");
    if (ImGui::IsItemClicked()) {
        ShellExecuteA(NULL, "open", "https://ko-fi.com/shadesofdeath", NULL, NULL, SW_SHOWNORMAL);
    }
    ImGui::PopStyleColor();
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Sürüm bilgisi
    ImGui::TextWrapped("%s: 1.0", T("Version").c_str());
    
    ImGui::Spacing();
    
    // Lisans bilgisi
    ImGui::TextWrapped("%s: Unlicense", T("License").c_str());
}

// Pencere boyutları
const int WINDOW_WIDTH = 1000; // Pencere genişliğini artır
const int WINDOW_HEIGHT = 650;

// WinMain - ana giriş
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // UTF-8 desteği için konsol kodlamasını ayarla
    SetConsoleOutputCP(CP_UTF8);
    
    // Uygulama genelinde UTF-8 karakter kodlamasını ayarla
    SetThreadUILanguage(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    
    // C++ locale'ını UTF-8 olarak ayarla
    try {
        std::locale::global(std::locale(".UTF-8"));
    }
    catch (const std::exception&) {
        try {
            std::locale::global(std::locale("C.UTF-8"));
        }
        catch (const std::exception&) {
            try {
                std::locale::global(std::locale("en_US.UTF-8"));
            }
            catch (const std::exception&) {
                // UTF-8 locale'ı ayarlanamadı, varsayılan ile devam et
                OutputDebugStringA("UTF-8 locale could not be set. Using default.\n");
            }
        }
    }
    
    // İlk başlangıç kontrolü
    bool isFirstStart = false;
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Twindows", 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        // Kayıt defterinde anahtarımız yoksa ilk başlangıçtır
        isFirstStart = true;
    } else {
        RegCloseKey(hKey);
    }
    
    // Bellek leak tespiti için debug flag'leri ayarla
    // Sadece debug modunda aktif olacak
    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif
    
    // Yapılandırılmış exception handling
    try {
        // Bellek optimizasyonlarını etkinleştir
        if (g_memOptimizationEnabled) {
            // Düşük RAM fragmentasyonu için bellek tahsisi davranışını ayarla
            ULONG HeapFragValue = HEAP_NO_SERIALIZE;
            HeapSetInformation(NULL, HeapCompatibilityInformation, 
                               &HeapFragValue, sizeof(HeapFragValue));
            
            // Bellek limitini 50MB olarak ayarla (düşük RAM kullanımı için)
            MemoryManager::SetMemoryLimit(50); // 50MB
            
            // Bellek kullanımını sınırla
            SetProcessWorkingSetSizeEx(GetCurrentProcess(), 8*1024*1024, 50*1024*1024, 
                                      QUOTA_LIMITS_HARDWS_MIN_DISABLE | 
                                      QUOTA_LIMITS_HARDWS_MAX_DISABLE);
        }

        // Yönetici izni kontrolü - HKEY_LOCAL_MACHINE erişimi için gerekli
        if (!IsRunAsAdmin()) {
            // Yönetici olarak yeniden başlat
            if (RestartAsAdmin()) {
                // Başarıyla yeniden başlatıldı, mevcut işlemi sonlandır
                return 0;
            }
            
            // Yeniden başlatma başarısız oldu, kullanıcıya bilgi ver
            MessageBoxA(NULL, 
                      "Bu uygulama bazı işlevler için yönetici izni gerektiriyor, ancak\n"
                      "yönetici olarak başlatılamadı. Bazı özellikler çalışmayabilir.", 
                      "Twindows", 
                      MB_OK | MB_ICONWARNING);
        }
        
        // Enable DPI awareness
        SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

        // Başlangıçta ayarları yükle
        LoadSettings();

        // Create application window (borderless)
        WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Twindows"), NULL };
        ::RegisterClassEx(&wc);
        
        // Get screen dimensions to center window
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int windowX = (screenWidth - WINDOW_WIDTH) / 2;
        int windowY = (screenHeight - WINDOW_HEIGHT) / 2;
        
        // Pencere oluştur
        HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Twindows - Windows Optimizer"), 
                                   WS_POPUP | WS_VISIBLE, // Sınırsız pencere için WS_POPUP kullan
                                   windowX, windowY, WINDOW_WIDTH, WINDOW_HEIGHT, 
                                   NULL, NULL, wc.hInstance, NULL);

        // Pencereyi yuvarlatılmış köşelerle oluştur
        const int radius = 10; // Köşe yuvarlatma derecesi
        
        // GDI nesnesi için doğru türü kullan
        HRGN region = CreateRoundRectRgn(0, 0, WINDOW_WIDTH + 1, WINDOW_HEIGHT + 1, radius, radius);
        
        if (region) {
            SetWindowRgn(hwnd, region, TRUE);
            // Windows bunu kopyaladığı için güvenle silebiliriz
            DeleteObject(region);
        }

        // Initialize Direct3D
        ID3D11Device* g_pd3dDevice = NULL;
        ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
        IDXGISwapChain* g_pSwapChain = NULL;
        ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 4; // MSAA 4x anti-aliasing kullan
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK) {
            return 1;
        }

        // Create render target
        ID3D11Texture2D* pBackBuffer;
        g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
        pBackBuffer->Release();

        // Show the window
        ::ShowWindow(hwnd, SW_SHOWDEFAULT);
        ::UpdateWindow(hwnd);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
        
        // Mevcut Windows temasını kontrol et ve uygun temayı uygula
        bool isDarkMode = IsWindowsInDarkMode();
        if (isDarkMode) {
            ApplyDarkTheme();
        } else {
            ApplyLightTheme();
        }
        
        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
        
        // Çoklu dil desteği için font yüklemelerini ayarla
        ImGuiIO& ioFonts = ImGui::GetIO();
        
        // Çoklu dil desteği (Temel Latin, Türkçe ve Batı Avrupa dilleri için)
        ImVector<ImWchar> multilingualGlyphRanges;
        ImFontGlyphRangesBuilder multiBuilder;
        multiBuilder.AddRanges(ioFonts.Fonts->GetGlyphRangesDefault()); // Latin karakterleri
        multiBuilder.AddRanges(ioFonts.Fonts->GetGlyphRangesGreek());   // Yunanca
        multiBuilder.AddText("ÇçĞğİıÖöŞşÜü"); // Türkçe özel karakterler
        multiBuilder.BuildRanges(&multilingualGlyphRanges);
        
        // En yaygın Windows fontlarını sıralı diziye koy
        const char* commonFontPaths[] = {
            "C:\\Windows\\Fonts\\segoeui.ttf",
            "C:\\Windows\\Fonts\\arial.ttf",
            "C:\\Windows\\Fonts\\calibri.ttf",
            "C:\\Windows\\Fonts\\consola.ttf"
        };
        
        // Font yapılandırması
        ImFontConfig fontConfig;
        fontConfig.MergeMode = false;
        fontConfig.PixelSnapH = true;
        fontConfig.OversampleH = 3; // Yüksek kalite için
        fontConfig.OversampleV = 3; 
        fontConfig.RasterizerMultiply = 1.5f; // Fontları daha kalın göster
        
        // Sabit font boyutu
        float fontSize = 18.0f;
        
        // Temel Latin karakterleri için varsayılan font yükle
        ImFont* defaultFont = ioFonts.Fonts->AddFontDefault();
        
        // Temel Latin ve Türkçe karakterler için font yükle
        ImFont* mainFont = nullptr;
        for (const char* fontPath : commonFontPaths) {
            if (FILE* f = fopen(fontPath, "rb")) {
                fclose(f);
                fontConfig.MergeMode = false;
                mainFont = ioFonts.Fonts->AddFontFromFileTTF(fontPath, fontSize, &fontConfig, multilingualGlyphRanges.Data);
                break;
            }
        }
        
        // Eğer hiçbir font yüklenemezse varsayılanı kullan
        if (!mainFont) mainFont = defaultFont;
        
        // Font atlas'ı oluştur
        ioFonts.Fonts->Build();

        // Create list of tweaks
        std::vector<Tweak> tweaks = {
            {"Disable File Explorer Ads", false, "Disables ads in File Explorer"},
            {"Disable Lock Screen Tips and Ads", false, "Disables lock screen tips and ads"},
            {"Disable Settings Ads", false, "Disables ads in Settings"},
            {"Disable General Tips and Ads", false, "Disables general tips and ads"},
            {"Disable \"Finish Setup\" Ads", false, "Disables ads during setup"},
            {"Disable \"Welcome Experience\" Ads", false, "Disables ads during the welcome experience"},
            {"Disable Personalized Ads", false, "Disables personalized ads"},
            {"Disable \"Tailored Experiences\"", false, "Disables tailored experiences"},
            {"Disable Start Menu Ads", false, "Disables ads in the Start Menu"},
            {"Disable \"Notification Suggestions\"", false, "Disables notification suggestions"},
            {"Disable Bing Results In Search", false, "Disables Bing results in search"},
            {"Disable Edge Search Bar Widget", false, "Disables Edge search bar widget"}
        };

        // Main loop
        bool done = false;
        bool allSelected = false;
        
        // AppX paketleri için değişkenler
        static bool isRemoving = false;
        static int lastRemovedCount = 0;
        static auto lastRemoveTime = std::chrono::steady_clock::now();
        static int currentPackageIndex = -1;
        static std::string currentPackageName = "";
        static char searchBuffer[256] = "";
        
        // Windows tema değişikliğini algılamak için zamanlayıcı
        ULONGLONG lastThemeCheckTime = GetTickCount64();
        bool lastDarkModeState = isDarkMode;
        ImVec4 lastAccentColor = GetWindowsAccentColor();

        while (!done) {
            // Poll and handle messages (inputs, window resize, etc.)
            MSG msg;
            while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    done = true;
            }
            if (done)
                break;
                
            // Bellek kullanımını kontrol et ve gerekirse optimize et
            if (g_memOptimizationEnabled) {
                MemoryManager::CheckAndOptimizeMemory();
            }
                
            // Her 1 saniyede bir tema değişikliğini kontrol et
            ULONGLONG currentTime = GetTickCount64();
            if (currentTime - lastThemeCheckTime > 1000) { // 1000 ms = 1 saniye
                lastThemeCheckTime = currentTime;
                
                // Mevcut tema modunu kontrol et
                bool currentDarkMode = IsWindowsInDarkMode();
                ImVec4 currentAccentColor = GetWindowsAccentColor();
                
                // Tema değişikliği veya aksan rengi değişikliği varsa uygula
                if (currentDarkMode != lastDarkModeState || 
                    lastAccentColor.x != currentAccentColor.x || 
                    lastAccentColor.y != currentAccentColor.y || 
                    lastAccentColor.z != currentAccentColor.z) {
                    
                    lastDarkModeState = currentDarkMode;
                    lastAccentColor = currentAccentColor;
                    
                    if (currentDarkMode) {
                        ApplyDarkTheme();
                    } else {
                        ApplyLightTheme();
                    }
                }
            }

            // Start the Dear ImGui frame
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // Create main window - with title bar but only close button
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

            // Configure window flags to show title bar with close button only
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | // Orijinal title bar'ı kaldır
                                            ImGuiWindowFlags_NoResize | 
                                            ImGuiWindowFlags_NoMove | 
                                            ImGuiWindowFlags_NoCollapse |
                                            ImGuiWindowFlags_NoScrollbar | 
                                            ImGuiWindowFlags_NoScrollWithMouse |
                                            ImGuiWindowFlags_NoNavFocus;

            // Köşe yuvarlaklaştırma için stilin korunduğundan emin ol
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f); // Yuvarlak köşeleri zorla
            ImGui::Begin("Twindows", nullptr, window_flags);
            ImGui::PopStyleVar(2); // İki stil değişkenini geri al

            // Başlık bölgesinin nerede olduğunu belirlemek için (sürükleme alanı)
            ImVec2 windowPos = ImGui::GetWindowPos();
            float headerBarHeight = TITLEBAR_HEIGHT;
            
            // Pencere genişliğini al
            float windowWidth = ImGui::GetWindowWidth();
            
            // Basit bir başlık ve kapatma butonu için alan
            ImGui::BeginGroup();
            
            // Başlık yazısını sol üste yerleştir
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f); // Dikeyde ortala
            ImGui::Text("Twindows");
            
            // Küçült butonunu sağ üst köşeye yerleştir
            ImGui::SameLine(windowWidth - 70.0f);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4.0f); // Yukarı taşı
            
            // Küçült butonunun stilini ayarla
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.4f, 0.4f, 0.5f)); // Gri
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.5f, 0.7f)); // Daha belirgin gri
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 0.9f)); // Tıklama rengi
            
            // Köşeleri yuvarlatma
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
            
            // Küçült butonu - Tire (-) ile göster
            if (ImGui::Button("-", ImVec2(25, 22))) {
                // Pencereyi küçült
                ShowWindow(hwnd, SW_MINIMIZE);
            }
            
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);
            
            // Kapat butonunu sağ üst köşeye yerleştir - biraz sola ve yukarı taşı
            ImGui::SameLine(windowWidth - 40.0f); // Sola doğru konumunu ayarla
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4.0f); // Yukarı taşı
            
            // Kapat butonunu daha belirgin yap
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.1f, 0.5f)); // Kırmızımsı
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 0.7f)); // Daha belirgin kırmızı
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.3f, 0.3f, 0.9f)); // Tıklama rengi
            
            // Köşeleri yuvarlatmadan kapat butonu göster ve büyüklüğünü küçült
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f); // Köşe yuvarlaklaştırmayı kapat
            
            // Kapat butonu - normal X ile göster ve biraz küçült
            if (ImGui::Button("X", ImVec2(25, 22))) {
                done = true; // Programı sonlandır
            }
            
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);
            
            ImGui::EndGroup();
            
            // Başlık çubuğu altına ince bir ayraç çiz
            ImGui::SetCursorPosY(headerBarHeight);
            ImVec4 separatorColor = lastDarkModeState ? 
                                  ImVec4(0.3f, 0.3f, 0.3f, 0.7f) : // Koyu temada hafif gri
                                  ImVec4(0.7f, 0.7f, 0.7f, 0.6f);  // Açık temada hafif gri
            ImGui::PushStyleColor(ImGuiCol_Separator, separatorColor);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5)); // Ayraç üstünde ve altında boşluk bırak
            ImGui::Separator();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
            
            // Normal içerik araya bir boşluk bırakarak başlasın
            ImGui::Dummy(ImVec2(0, 5)); // 5 piksel dikey boşluk
            
            // Tab menüleri ekle
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 8)); // Tab butonlarına biraz padding ekle
            
            // Tab stil renklerini aksan rengine göre ayarla
            ImVec4 accentColor = GetWindowsAccentColor();
            ImGui::PushStyleColor(ImGuiCol_Tab, lastDarkModeState ? 
                                ImVec4(accentColor.x * 0.5f, accentColor.y * 0.5f, accentColor.z * 0.5f, 0.8f) : // Koyu tema tab
                                ImVec4(accentColor.x * 0.7f, accentColor.y * 0.7f, accentColor.z * 0.7f, 0.7f)); // Açık tema tab
            ImGui::PushStyleColor(ImGuiCol_TabHovered, lastDarkModeState ? 
                                ImVec4(accentColor.x * 0.7f, accentColor.y * 0.7f, accentColor.z * 0.7f, 0.8f) : // Koyu tema hover
                                ImVec4(accentColor.x * 0.8f, accentColor.y * 0.8f, accentColor.z * 0.8f, 0.8f)); // Açık tema hover
            ImGui::PushStyleColor(ImGuiCol_TabActive, lastDarkModeState ? 
                                ImVec4(accentColor.x * 0.6f, accentColor.y * 0.6f, accentColor.z * 0.6f, 1.0f) : // Koyu tema aktif
                                ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.0f)); // Açık tema aktif
            
            // Statik bir değişken olarak seçili tab indeksini sakla
            static int currentTab = 0;
            
            // Tab bar'ı metin boyutuna göre büyümesine izin verecek şekilde ayarla
            ImGuiTabBarFlags tabFlags = ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton;
            
            if (ImGui::BeginTabBar("MainTabBar", tabFlags)) {
                if (ImGui::BeginTabItem(T("Privacy").c_str())) {
                    currentTab = 0;
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(T("Performance").c_str())) {
                    currentTab = 1;
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(T("Appearance").c_str())) {
                    currentTab = 2;
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(T("Security").c_str())) {
                    currentTab = 3;
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(T("AppX Packages").c_str())) {
                    currentTab = 4;
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(T("Settings").c_str())) {
                    currentTab = 5;
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(T("About").c_str())) {
                    currentTab = 6;
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            
            ImGui::PopStyleColor(3); // Tab renk stillerini geri al
            ImGui::PopStyleVar(); // Frame padding stil değişkenini geri al
            
            ImGui::Spacing();
            
            // Seçilen tab'a göre içerik göster
            switch (currentTab) {
                case 0: // Privacy
                {
                    ImGui::Text("%s", T("Windows Tweaker - Privacy Settings").c_str());
                    ImGui::Separator();
                    ImGui::Spacing();

                    // Scrollable bölge ekle
                    ImGui::BeginChild("PrivacyScrollRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false);

                    // Yeni privacy tweaks yapısını kullan
                    for (size_t i = 0; i < privacyTweaks.size(); i++) {
                        // Checkbox'tan önce durumu kaydet
                        bool prevState = privacyTweaks[i].enabled;
                        
                        // Checkbox göster - buna tıklanırsa enabled değeri değişecek
                        if (ImGui::Checkbox(T(privacyTweaks[i].name).c_str(), &privacyTweaks[i].enabled)) {
                            // Değişiklik oldu, registry değerini güncelle
                            ApplyPrivacyTweak(privacyTweaks[i]);
                            
                            // Tanılama amaçlı log ekle
                            std::string debugInfo = "Privacy tweak changed: " + privacyTweaks[i].name + 
                                " = " + (privacyTweaks[i].enabled ? "enabled" : "disabled") + "\n";
                            OutputDebugStringA(debugInfo.c_str());
                        }
                        
                        // Tooltip göster
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("%s", T(privacyTweaks[i].tooltip).c_str());
                        }
                        
                        // Çok uzun tweaks listesi için biraz boşluk ekle
                        if (i == privacyTweaks.size() / 2) {
                            ImGui::SameLine(windowWidth / 2 + 20);
                            ImGui::NewLine();
                        }
                    }
                    
                    ImGui::EndChild(); // Scroll bölgesini kapat
                    
                    break;
                }
                    
                case 1: // Performance
                {
                    ImGui::Text("%s", T("Windows Tweaker - Performance Settings").c_str());
                    ImGui::Separator();
                    ImGui::Spacing();

                    // Scrollable bölge ekle
                    ImGui::BeginChild("PerformanceScrollRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false);

                    // Yeni performance tweaks yapısını kullan
                    for (size_t i = 0; i < performanceTweaks.size(); i++) {
                        // Checkbox'tan önce durumu kaydet
                        bool prevState = performanceTweaks[i].enabled;
                        
                        // Checkbox göster - T() fonksiyonu ile çevirme ekle
                        if (ImGui::Checkbox(T(performanceTweaks[i].name).c_str(), &performanceTweaks[i].enabled)) {
                            // Değişiklik oldu, registry değerini güncelle
                            ApplyPerformanceTweak(performanceTweaks[i]);
                            
                            // Tanılama amaçlı log ekle
                            std::string debugInfo = "Performance tweak changed: " + performanceTweaks[i].name + 
                                " = " + (performanceTweaks[i].enabled ? "enabled" : "disabled") + "\n";
                            OutputDebugStringA(debugInfo.c_str());
                        }
                        
                        // Tooltip göster - T() fonksiyonu ile çevirme ekle
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("%s", T(performanceTweaks[i].tooltip).c_str());
                        }
                        
                        // Çok uzun tweaks listesi için biraz boşluk ekle
                        if (i == performanceTweaks.size() / 2) {
                            ImGui::SameLine(windowWidth / 2 + 20);
                            ImGui::NewLine();
                        }
                    }
                    
                    ImGui::EndChild(); // Scroll bölgesini kapat
                    
                    break;
                }
                
                case 2: // Appearance
                {
                    ImGui::Text("%s", T("Windows Tweaker - Appearance Settings").c_str());
                    ImGui::Separator();
                    ImGui::Spacing();

                    // Panel yüksekliği
                    const float panelHeight = 30.0f;
                    // Panel ile ana pencere arasındaki boşluk için margin
                    const float marginBottom = 5.0f;
                    
                    // Scrollable bölge ekle - panelin tam yukarısında bitmesi için yüksekliği ayarla
                    ImGui::BeginChild("AppearanceScrollRegion", 
                                      ImVec2(0, -panelHeight - marginBottom - ImGui::GetFrameHeightWithSpacing()), 
                                      false);

                    // Yeni appearance tweaks yapısını kullan
                    for (size_t i = 0; i < appearanceTweaks.size(); i++) {
                        // Checkbox'tan önce durumu kaydet
                        bool prevState = appearanceTweaks[i].enabled;
                        
                        // Checkbox göster - T() fonksiyonu ile çevirme ekle
                        if (ImGui::Checkbox(T(appearanceTweaks[i].name).c_str(), &appearanceTweaks[i].enabled)) {
                            // Değişiklik oldu, registry değerini güncelle
                            ApplyAppearanceTweak(appearanceTweaks[i]);
                            
                            // Tanılama amaçlı log ekle
                            std::string debugInfo = "Appearance tweak changed: " + appearanceTweaks[i].name + 
                                " = " + (appearanceTweaks[i].enabled ? "enabled" : "disabled") + "\n";
                            OutputDebugStringA(debugInfo.c_str());
                        }
                        
                        // Tooltip göster - T() fonksiyonu ile çevirme ekle
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("%s", T(appearanceTweaks[i].tooltip).c_str());
                        }
                        
                        // Çok uzun tweaks listesi için biraz boşluk ekle
                        if (i == appearanceTweaks.size() / 2) {
                            ImGui::SameLine(windowWidth / 2 + 20);
                            ImGui::NewLine();
                        }
                    }
                    
                    ImGui::EndChild(); // Scroll bölgesini kapat
                    
                    // Paneli ekranın en altına yerleştir (dummy kullanmadan)
                    ImGui::SetCursorPosY(ImGui::GetWindowHeight() - panelHeight - ImGui::GetStyle().WindowPadding.y);
                    
                    // Tema durumuna göre renkleri belirle
                    ImVec4 bgColor, textColor, inactiveTextColor;
                    
                    if (lastDarkModeState) {
                        // Koyu temada panel renkleri
                        bgColor = NeedsExplorerRestart() ? 
                                 ImVec4(0.9f, 0.6f, 0.3f, 0.2f) : // Değişiklik varsa turuncu
                                 ImVec4(0.5f, 0.5f, 0.5f, 0.1f);  // Değişiklik yoksa gri
                        textColor = ImVec4(1.0f, 0.8f, 0.0f, 1.0f); // Koyu temada sarı/turuncu
                        inactiveTextColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Koyu temada gri
                    } else {
                        // Açık temada panel renkleri - daha belirgin
                        bgColor = NeedsExplorerRestart() ? 
                                 ImVec4(1.0f, 0.8f, 0.3f, 0.25f) : // Değişiklik varsa daha parlak turuncu
                                 ImVec4(0.5f, 0.5f, 0.5f, 0.1f);   // Değişiklik yoksa gri
                        textColor = ImVec4(0.9f, 0.5f, 0.0f, 1.0f); // Açık temada koyu turuncu
                        inactiveTextColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Açık temada daha koyu gri
                    }
                    
                    // Panel arka planını hafif renklendir
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, bgColor);
                    
                    // Panel yüksekliğini 30 piksel olarak ayarla ve en altta göster
                    ImGui::BeginChild("ExplorerRestartNotice", ImVec2(0, panelHeight), true);
                    
                    // Yatay hizalamayı ayarla
                    float panelWidth = ImGui::GetContentRegionAvail().x;
                    float textWidth = 0.0f;
                    float spacing = 15.0f; // Daha az boşluk bırak
                    
                    // Değişiklik varsa uyarı ve buton göster, yoksa sadece bilgi mesajı
                    if (NeedsExplorerRestart()) {
                        // Uyarı metni
                        textWidth = ImGui::CalcTextSize(T("Appearance Changes Notice").c_str()).x;
                        
                        // Dinamik buton boyutu için buton metninin genişliğini hesapla
                        // ve biraz ekstra boşluk ekle
                        float buttonTextWidth = ImGui::CalcTextSize(T("Restart Explorer").c_str()).x;
                        float buttonWidth = buttonTextWidth + 30.0f; // Her iki tarafta 15px boşluk
                        
                        // Daha iyi ortalama için metni ve butonu yan yana yerleştir
                        // ve birlikte ortala
                        float totalWidth = textWidth + spacing + buttonWidth;
                        float startX = (panelWidth - totalWidth) / 2;
                        
                        // Metni yerleştir
                        ImGui::SetCursorPosX(startX);
                        // Dikeyde tam ortala
                        ImGui::SetCursorPosY((panelHeight - ImGui::GetTextLineHeightWithSpacing()) / 2);
                        ImGui::TextColored(textColor, "%s", T("Appearance Changes Notice").c_str());
                        
                        // Restart Explorer butonu - metinden hemen sonra
                        ImGui::SameLine(0, spacing);
                        
                        // Butonu biraz daha belirgin yap - açık/koyu tema farkı
                        if (lastDarkModeState) {
                            // Koyu tema buton renkleri
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.5f, 0.1f, 0.6f)); // Turuncu-amber
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.6f, 0.1f, 0.8f));
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.7f, 0.2f, 1.0f));
                        } else {
                            // Açık tema buton renkleri - daha koyu ve belirgin
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.5f, 0.0f, 0.7f)); // Koyu turuncu
                            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.6f, 0.0f, 0.8f));
                            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.7f, 0.0f, 1.0f));
                        }
                        
                        // Butonu dikeyde ortala
                        float buttonY = (panelHeight - ImGui::GetFrameHeightWithSpacing()) / 2;
                        ImGui::SetCursorPosY(buttonY);
                        
                        // Butonu dinamik genişlikte çiz
                        if (ImGui::Button(T("Restart Explorer").c_str(), ImVec2(buttonWidth, 0))) {
                            RestartExplorer();
                        }
                        
                        ImGui::PopStyleColor(3); // Buton stillerini geri al
                    } else {
                        // Sadece bilgi mesajı - ortala
                        textWidth = ImGui::CalcTextSize(T("No appearance changes requiring restart").c_str()).x;
                        ImGui::SetCursorPosX((panelWidth - textWidth) / 2);
                        // Dikeyde tam ortala
                        ImGui::SetCursorPosY((panelHeight - ImGui::GetTextLineHeightWithSpacing()) / 2);
                        ImGui::TextColored(inactiveTextColor, "%s", T("No appearance changes requiring restart").c_str());
                    }
                    
                    ImGui::EndChild();
                    ImGui::PopStyleColor();
                    
                    break;
                }
                    
                case 3: // Security
                {
                    ImGui::Text("%s", T("Windows Tweaker - Security Settings").c_str());
                    ImGui::Separator();
                    ImGui::Spacing();
                    
                    // Scrollable bölge ekle
                    ImGui::BeginChild("SecurityScrollRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false);
                    
                    for (size_t i = 0; i < securityTweaks.size(); i++) {
                        // Checkbox'tan önce durumu kaydet
                        bool prevState = securityTweaks[i].enabled;
                        
                        // Checkbox göster - T() fonksiyonu ile çevirme ekle
                        if (ImGui::Checkbox(T(securityTweaks[i].name).c_str(), &securityTweaks[i].enabled)) {
                            // Değişiklik oldu, registry değerini güncelle
                            ApplySecurityTweak(securityTweaks[i]);
                            
                            // Tanılama amaçlı log ekle
                            std::string debugInfo = "Security tweak changed: " + securityTweaks[i].name + 
                                " = " + (securityTweaks[i].enabled ? "enabled" : "disabled") + "\n";
                            OutputDebugStringA(debugInfo.c_str());
                        }
                        
                        // Tooltip göster - T() fonksiyonu ile çevirme ekle
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("%s", T(securityTweaks[i].tooltip).c_str());
                        }
                        
                        // Çok uzun tweaks listesi için biraz boşluk ekle
                        if (i == securityTweaks.size() / 2) {
                            ImGui::SameLine(windowWidth / 2 + 20);
                            ImGui::NewLine();
                        }
                    }
                    
                    ImGui::EndChild(); // Scroll bölgesini kapat
                    
                    break;
                }
                
                case 4: // AppX Packages
                {
                    ImGui::Text("%s", T("Windows Tweaker - AppX Packages").c_str());
                    ImGui::Separator();
                    ImGui::Spacing();
                    
                    // Üst panel için daha iyi düzen
                    float windowWidth = ImGui::GetContentRegionAvail().x;
                    float searchWidth = windowWidth * 0.30f; // Pencere genişliğine göre oran
                    float buttonSpacing = 10.0f;
                    float leftPanelWidth = searchWidth + 100.0f; // Arama alanı ve etiketi için
                    
                    // Arama alanını ve etiketi bir grup içine al
                    ImGui::BeginGroup();
                    ImGui::Text("%s:", T("Search apps").c_str());
                    ImGui::SameLine();
                    ImGui::PushItemWidth(searchWidth);
                    ImGui::InputText("##search", searchBuffer, IM_ARRAYSIZE(searchBuffer));
                    ImGui::PopItemWidth();
                    ImGui::EndGroup();
                    
                    // Sağda butonlar için yer bırak - Butonları sağa hizala
                    float remainingWidth = windowWidth - leftPanelWidth;
                    float selectButtonWidth = ImGui::CalcTextSize(T("Select All").c_str()).x + 20.0f;
                    float deselectButtonWidth = ImGui::CalcTextSize(T("Deselect All").c_str()).x + 20.0f;
                    
                    // "Remove Selected Apps" butonu için dinamik genişlik
                    float removeButtonWidth = ImGui::CalcTextSize(T("Remove Selected Apps").c_str()).x + 30.0f;
                    
                    // İşlem durumunu gösteren metinler için daha fazla alan
                    if (isRemoving) {
                        removeButtonWidth = ImGui::CalcTextSize(T("Removing apps...").c_str()).x + 30.0f;
                    } else if (lastRemovedCount > 0) {
                        std::string message = T("Successfully removed");
                        message += " " + std::to_string(lastRemovedCount) + " " + T("application(s)");
                        removeButtonWidth = ImGui::CalcTextSize(message.c_str()).x + 30.0f;
                    }
                    
                    // Sağa hizala ve butonları yerleştir
                    ImGui::SameLine(windowWidth - (selectButtonWidth + deselectButtonWidth + removeButtonWidth + 2*buttonSpacing));
                    
                    // Tümünü seç/kaldır butonları
                    if (ImGui::Button(T("Select All").c_str(), ImVec2(selectButtonWidth, 0))) {
                        for (auto& package : appxPackages) {
                            // Sistem uygulamalarını seçme
                            if (package.displayName.find("(System)") == std::string::npos) {
                                package.isSelected = true;
                            }
                        }
                    }
                    
                    ImGui::SameLine(0, buttonSpacing);
                    if (ImGui::Button(T("Deselect All").c_str(), ImVec2(deselectButtonWidth, 0))) {
                        for (auto& package : appxPackages) {
                            package.isSelected = false;
                        }
                    }
                    
                    ImGui::SameLine(0, buttonSpacing);
                    
                    // Kaldırma butonunun durumu
                    bool anySelected = false;
                    for (const auto& package : appxPackages) {
                        if (package.isSelected) {
                            anySelected = true;
                            break;
                        }
                    }
                    
                    if (isRemoving) {
                        // Kaldırma işlemi devam ediyor - kırmızı buton
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.3f, 0.3f, 0.6f));
                        ImGui::Button(T("Removing apps...").c_str(), ImVec2(removeButtonWidth, 0));
                        ImGui::PopStyleColor();
                        
                        // 15 saniye sonra mesajı gizle (zaman aşımı için)
                        auto now = std::chrono::steady_clock::now();
                        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastRemoveTime).count() > 15) {
                            isRemoving = false;
                            currentPackageIndex = -1;
                            currentPackageName = "";
                        }
                    } else if (lastRemovedCount > 0) {
                        // Kaldırma tamamlandı - yeşil buton
                        std::string message = T("Successfully removed");
                        message += " " + std::to_string(lastRemovedCount) + " " + T("application(s)");
                        
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.8f, 0.3f, 0.6f));
                        ImGui::Button(message.c_str(), ImVec2(removeButtonWidth, 0));
                        ImGui::PopStyleColor();
                        
                        // 5 saniye sonra mesajı gizle
                        auto now = std::chrono::steady_clock::now();
                        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastRemoveTime).count() > 5) {
                            lastRemovedCount = 0;
                        }
                    } else if (ImGui::Button(T("Remove Selected Apps").c_str(), ImVec2(removeButtonWidth, 0))) {
                        // Kaldırma işlemi başlat
                        if (anySelected) {
                            isRemoving = true;
                            
                            // Kaldırma işlemini arka planda başlat
                            std::thread removeThread([&]() {
                                int removed = 0;
                                
                                for (size_t i = 0; i < appxPackages.size(); i++) {
                                    if (appxPackages[i].isSelected) {
                                        // Şu an kaldırılan paketi güncelle
                                        currentPackageIndex = static_cast<int>(i);
                                        currentPackageName = appxPackages[i].displayName;
                                        
                                        if (RemoveAppXPackage(appxPackages[i].packageName)) {
                                            removed++;
                                            appxPackages[i].isSelected = false;
                                        }
                                        
                                        // UI'ın güncellenmesi için kısa bir bekleme
                                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                    }
                                }
                                
                                // İşlem tamamlandı
                                lastRemovedCount = removed;
                                lastRemoveTime = std::chrono::steady_clock::now();
                                isRemoving = false;
                                currentPackageIndex = -1;
                                currentPackageName = "";
                            });
                            
                            // Thread'i ayrı çalıştır
                            removeThread.detach();
                        } else {
                            // Hiçbir uygulama seçilmedi
                            ImGui::OpenPopup("NoAppsSelected");
                        }
                    }
                    
                    // Hiçbir uygulama seçilmediğinde gösterilen popup
                    if (ImGui::BeginPopupModal("NoAppsSelected", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                        ImGui::Text("%s", T("No apps selected").c_str());
                        ImGui::Separator();
                        
                        if (ImGui::Button("OK", ImVec2(120, 0))) {
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::EndPopup();
                    }
                    
                    // Eğer seçim devre dışıysa veya kaldırma devam ediyorsa butonu devre dışı bırak
                    if (!anySelected || isRemoving) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 0.6f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 0.6f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.5f, 0.6f));
                        ImGui::PopStyleColor(3);
                    }
                    
                    ImGui::Spacing();
                    
                    // Kaldırma işlemi sırasında o anki durumu göster
                    if (isRemoving && currentPackageIndex >= 0) {
                        ImGui::Separator();
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.65f, 0.0f, 1.0f)); // Turuncu
                        ImGui::Text("%s: %s", T("Removing").c_str(), currentPackageName.c_str());
                        
                        // İlerleme göstergesi ekle
                        int totalSelected = 0;
                        int processedCount = 0;
                        
                        for (size_t i = 0; i < appxPackages.size(); i++) {
                            if (appxPackages[i].isSelected || (i <= static_cast<size_t>(currentPackageIndex) && !appxPackages[i].isSelected && lastRemovedCount > 0)) {
                                totalSelected++;
                                if (i <= static_cast<size_t>(currentPackageIndex)) {
                                    processedCount++;
                                }
                            }
                        }
                        
                        if (totalSelected > 0) {
                            float progress = static_cast<float>(processedCount) / static_cast<float>(totalSelected);
                            ImGui::ProgressBar(progress, ImVec2(-1, 0), (std::to_string(processedCount) + "/" + std::to_string(totalSelected)).c_str());
                        }
                        
                        ImGui::PopStyleColor();
                        ImGui::Separator();
                    }
                    
                    // Scrollable bölge ekle
                    ImGui::BeginChild("AppXPackagesScrollRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false);
                    
                    // Sistem uygulamaları için uyarı
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.4f, 0.1f, 1.0f));
                    ImGui::TextWrapped("%s: %s", T("System Apps").c_str(), T("Warning: System apps are essential for Windows").c_str());
                    ImGui::PopStyleColor();
                    ImGui::Separator();
                    
                    // Uygulamaları 3 sütun halinde göster - sütun genişliğini ayarla
                    const float columnWidth = (windowWidth / 3.0f) - 15.0f;
                    int columnCounter = 0;
                    
                    for (size_t i = 0; i < appxPackages.size(); i++) {
                        // Arama için küçük harfe çevirme işlemleri
                        std::string searchLower = searchBuffer;
                        std::string packageNameLower = appxPackages[i].packageName;
                        std::string displayNameLower = appxPackages[i].displayName;
                        
                        // Küçük harfe çevir
                        for (char& c : searchLower) c = std::tolower(c);
                        for (char& c : packageNameLower) c = std::tolower(c);
                        for (char& c : displayNameLower) c = std::tolower(c);
                        
                        // Arama yapılıyorsa ve eşleşmiyorsa atlayalım
                        if (strlen(searchBuffer) > 0 && 
                            packageNameLower.find(searchLower) == std::string::npos && 
                            displayNameLower.find(searchLower) == std::string::npos) {
                            continue;
                        }
                        
                        // Yeni sütuna geçme kontrolü
                        if (columnCounter % 3 == 0 && columnCounter > 0) {
                            ImGui::NextColumn();
                        }
                        
                        // Her sütun için grup oluştur
                        ImGui::BeginGroup();
                        
                        // Sistem uygulamalarını farklı renklendir
                        if (appxPackages[i].displayName.find("(System)") != std::string::npos) {
                            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.7f); // Daha az soluk görünüm
                            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.5f, 0.0f, 1.0f)); // Turuncu metin - uyarı işareti
                            
                            // Yeterli genişlik için checkbox'u düzenle - metin kırpılmasını önle
                            bool isSelected = appxPackages[i].isSelected;
                            std::string label = appxPackages[i].displayName;
                            
                            // Metin çok uzunsa kırp
                            if (label.length() > 30) {
                                label = label.substr(0, 27) + "...";
                            }
                            
                            if (ImGui::Checkbox(label.c_str(), &appxPackages[i].isSelected)) {
                                // Checkbox değeri değişti - işlem yapılabilir
                            }
                            
                            ImGui::PopStyleColor();
                            ImGui::PopStyleVar();
                        } else {
                            // Normal uygulamalar için checkbox
                            std::string label = appxPackages[i].displayName;
                            
                            // Metin çok uzunsa kırp
                            if (label.length() > 30) {
                                label = label.substr(0, 27) + "...";
                            }
                            
                            ImGui::Checkbox(label.c_str(), &appxPackages[i].isSelected);
                        }
                        
                        // Tooltip
                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                            
                            // Sistem uygulamaları için uyarı göster
                            if (appxPackages[i].displayName.find("(System)") != std::string::npos) {
                                ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "%s", T("Warning: System apps are essential for Windows").c_str());
                            }
                            
                            // Tam paket adını göster
                            ImGui::Text("Package: %s", appxPackages[i].packageName.c_str());
                            ImGui::Text("Publisher: %s", appxPackages[i].publisher.c_str());
                            
                            ImGui::PopTextWrapPos();
                            ImGui::EndTooltip();
                        }
                        
                        ImGui::EndGroup();
                        
                        // Sütun düzenini sağla
                        columnCounter++;
                        if (columnCounter % 3 != 0) {
                            ImGui::SameLine(((columnCounter % 3) * columnWidth) + 5.0f);
                        }
                    }
                    
                    ImGui::EndChild(); // Scroll bölgesini kapat
                    
                    break;
                }
                    
                case 5: // Settings
                {
                    DrawSettingsTab();
                    
                    break;
                }
                    
                case 6: // About
                {
                    DrawAboutTab();
                    
                    break;
                }
            }
            
            ImGui::End();

            // Rendering
            ImGui::Render();
            const float clear_color_with_alpha[4] = { 
                lastDarkModeState ? 0.04f : 0.94f,
                lastDarkModeState ? 0.04f : 0.94f,
                lastDarkModeState ? 0.04f : 0.94f,
                1.00f
            };
                
            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            g_pSwapChain->Present(1, 0); // Present with vsync
        }

        // Kapanırken ayarları kaydet
        SaveSettings();
        
        // Kapanmadan önce belleği temizle
        if (g_memOptimizationEnabled) {
            // Tüm kullanılmayan belleği serbest bırak
            EmptyWorkingSet(GetCurrentProcess());
            // Heap fragmantasyonunu azalt
            MemoryManager::CompactHeap();
        }

        // Cleanup
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
        if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
        if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
        if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }

        ::DestroyWindow(hwnd);
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);

        return 0;
    } catch (const std::exception& e) {
        MessageBoxA(NULL, e.what(), "Twindows Error", MB_OK | MB_ICONERROR);
        return 1;
    }
} 