#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "windows_utils.h" // Windows API utility functions
#include <winreg.h>

// CMD komutlarını gizli çalıştırmak için dışardan tanımlanan fonksiyon - Eskiden kullanılan
extern bool ExecuteCommandSilent(const char* command);

// Structure to hold appearance tweak information
struct AppearanceTweak {
    std::string name;
    std::string tooltip;
    std::string enableCommand;  // Uyumluluk için tutuyoruz
    std::string disableCommand; // Uyumluluk için tutuyoruz
    bool enabled;
};

// Değişiklikler için Explorer'ın yeniden başlatılması gerekip gerekmediğini takip eden değişken
static bool explorerRestartNeeded = false;

// Değişiklikler için Explorer'ın yeniden başlatılması gerekip gerekmediğini döndür
inline bool NeedsExplorerRestart() {
    return explorerRestartNeeded;
}

// Explorer'ı yeniden başlatma ihtiyacını ayarla veya temizle
inline void SetExplorerRestartNeeded(bool needed) {
    explorerRestartNeeded = needed;
}

// Explorer'ı yeniden başlat ve flag'i temizle
inline void RestartExplorer() {
    WindowsUtils::RestartExplorer();
    explorerRestartNeeded = false;
}

// Hem HKCU hem de HKLM'de registry değerini kontrol et
inline bool AppearanceCheckRegistry(const char* keyPath, const char* valueName, DWORD expectedValue) {
    DWORD value = 0;
    
    // Önce HKEY_CURRENT_USER'da ara
    bool valueExists = WindowsUtils::GetRegistryValueDWORD(HKEY_CURRENT_USER, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // HKEY_CURRENT_USER'da bulunamadıysa HKEY_LOCAL_MACHINE'de ara
    valueExists = WindowsUtils::GetRegistryValueDWORD(HKEY_LOCAL_MACHINE, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// HKLM registry değerini kontrol et
inline bool AppearanceCheckRegistryHKLM(const char* keyPath, const char* valueName, DWORD expectedValue) {
    DWORD value = 0;
    bool valueExists = WindowsUtils::GetRegistryValueDWORD(HKEY_LOCAL_MACHINE, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// HKCU registry değerini kontrol et
inline bool AppearanceCheckRegistryHKCU(const char* keyPath, const char* valueName, DWORD expectedValue) {
    DWORD value = 0;
    bool valueExists = WindowsUtils::GetRegistryValueDWORD(HKEY_CURRENT_USER, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// HKCU string registry değerini kontrol et
inline bool AppearanceCheckRegistryStringHKCU(const char* keyPath, const char* valueName, const char* expectedValue) {
    std::string value;
    bool valueExists = WindowsUtils::GetRegistryValueString(HKEY_CURRENT_USER, keyPath, valueName, value);
    
    if (valueExists) {
        return value == expectedValue;
    }
    
    return false;
}

// Users (.DEFAULT) için registry değerini kontrol et
inline bool AppearanceCheckRegistryUsers(const char* keyPath, const char* valueName, const char* expectedValue) {
    HKEY hKey;
    char buffer[256] = {0};
    DWORD bufferSize = sizeof(buffer);
    bool result = false;
    
    if (RegOpenKeyExA(HKEY_USERS, keyPath, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, valueName, NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS) {
            result = (strcmp(buffer, expectedValue) == 0);
        }
        RegCloseKey(hKey);
    }
    
    return result;
}

// Klasik sağ tık menüsünün etkin olup olmadığını kontrol et
inline bool IsClassicRightClickEnabled() {
    HKEY hKey;
    bool result = false;
    
    if (RegOpenKeyExA(HKEY_CURRENT_USER, 
                      "Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32", 
                      0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        result = true;
        RegCloseKey(hKey);
    }
    
    return result;
}

// Galeri kenar çubuğu öğesinin kaldırılıp kaldırılmadığını kontrol et
inline bool IsGalleryRemovedFromPane() {
    DWORD value = 0;
    bool valueExists = WindowsUtils::GetRegistryValueDWORD(HKEY_CURRENT_USER, 
                                                          "Software\\Classes\\CLSID\\{e88865ea-0e1c-4e20-9aa6-edcd0212c87c}", 
                                                          "System.IsPinnedToNameSpaceTree", value);
    
    if (valueExists) {
        return value == 0;  // 0 = kaldırıldı, 1 = gösteriliyor
    }
    
    return true;  // Varsayılan olarak kaldırılmış kabul et
}

// Apply appearance tweak using WindowsUtils API
inline void ApplyAppearanceTweak(AppearanceTweak& tweak) {
    if (tweak.name == "Disable Bing Search in Start Menu") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Search", 
                "BingSearchEnabled", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Search", 
                "BingSearchEnabled", 1);
        }
    }
    else if (tweak.name == "Center Taskbar Icons") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "TaskbarAl", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "TaskbarAl", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Enable Dark Mode") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 
                "AppsUseLightTheme", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 
                "SystemUsesLightTheme", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 
                "AppsUseLightTheme", 1);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 
                "SystemUsesLightTheme", 1);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Show Detailed BSoD") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\CrashControl", 
                "DisplayParameters", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\CrashControl", 
                "DisplayParameters", 0);
        }
    }
    else if (tweak.name == "Enable Mouse Acceleration") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseSpeed", "1");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold1", "6");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold2", "10");
        } else {
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseSpeed", "0");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold1", "0");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold2", "0");
        }
    }
    else if (tweak.name == "Enable NumLock on Startup") {
        HKEY hKey;
        if (RegOpenKeyExA(HKEY_USERS, 
                         ".DEFAULT\\Control Panel\\Keyboard", 
                         0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
            
            const char* value = tweak.enabled ? "2" : "0";
            RegSetValueExA(hKey, "InitialKeyboardIndicators", 0, REG_SZ, 
                          (const BYTE*)value, strlen(value) + 1);
            
            RegCloseKey(hKey);
        }
    }
    else if (tweak.name == "Show Search Button in Taskbar") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", 
                "SearchboxTaskbarMode", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", 
                "SearchboxTaskbarMode", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Show File Extensions") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "HideFileExt", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "HideFileExt", 1);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Show Hidden Files") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "Hidden", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "Hidden", 2);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Enable Snap Assist Flyout") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "EnableSnapAssistFlyout", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "EnableSnapAssistFlyout", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Enable Snap Assist Suggestion") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "SnapAssist", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "SnapAssist", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Enable Snap Window") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "EnableSnapBar", 1);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Control Panel\\Desktop", 
                "WindowArrangementActive", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "EnableSnapBar", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Control Panel\\Desktop", 
                "WindowArrangementActive", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Enable Sticky Keys") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Accessibility\\StickyKeys", 
                "Flags", "510");
        } else {
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Accessibility\\StickyKeys", 
                "Flags", "26");
        }
    }
    else if (tweak.name == "Show Task View Button in Taskbar") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "ShowTaskViewButton", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "ShowTaskViewButton", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Show Verbose Messages During Logon") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "VerboseStatus", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "VerboseStatus", 0);
        }
    }
    else if (tweak.name == "Show Widgets Button in Taskbar") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "TaskbarDa", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
                "TaskbarDa", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Enable Classic Right-Click Menu") {
        if (tweak.enabled) {
            // Klasik menüyü etkinleştir - önce ana anahtarı oluştur
            HKEY hKey;
            if (RegCreateKeyExA(HKEY_CURRENT_USER, 
                               "Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}", 
                               0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
            }
            
            // Sonra InprocServer32 alt anahtarını oluştur
            if (RegCreateKeyExA(HKEY_CURRENT_USER, 
                               "Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32", 
                               0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
                // Boş değer ekle
                RegSetValueExA(hKey, "", 0, REG_SZ, (const BYTE*)"", 1);
                RegCloseKey(hKey);
            }
        } else {
            // Anahtarı tamamen sil - modern menüye dön
            RegDeleteKeyA(HKEY_CURRENT_USER, 
                         "Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32");
            RegDeleteKeyA(HKEY_CURRENT_USER, 
                         "Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}");
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Remove Gallery from Navigation Pane") {
        if (tweak.enabled) {
            // Galeriyi kaldır (0)
            HKEY hKey;
            if (RegCreateKeyExA(HKEY_CURRENT_USER, 
                               "Software\\Classes\\CLSID\\{e88865ea-0e1c-4e20-9aa6-edcd0212c87c}", 
                               0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
                DWORD value = 0;
                RegSetValueExA(hKey, "System.IsPinnedToNameSpaceTree", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
                RegCloseKey(hKey);
            }
        } else {
            // Galeriyi göster (1)
            HKEY hKey;
            if (RegCreateKeyExA(HKEY_CURRENT_USER, 
                               "Software\\Classes\\CLSID\\{e88865ea-0e1c-4e20-9aa6-edcd0212c87c}", 
                               0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
                DWORD value = 1;
                RegSetValueExA(hKey, "System.IsPinnedToNameSpaceTree", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));
                RegCloseKey(hKey);
            }
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Hide Personalized Web Recommendations") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Policies\\Microsoft\\Windows\\Explorer", 
                "HideRecommendedPersonalizedSites", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Policies\\Microsoft\\Windows\\Explorer", 
                "HideRecommendedPersonalizedSites", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Hide Recommended Section in Start Menu") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Policies\\Microsoft\\Windows\\Explorer", 
                "HideRecommendedSection", 1);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "HideRecommendedSection", 1);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "Intellimenus", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Policies\\Microsoft\\Windows\\Explorer", 
                "HideRecommendedSection", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "HideRecommendedSection", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "Intellimenus", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Hide Clock in System Tray") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "HideClock", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "HideClock", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Hide Meet Now Icon") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "HideSCAMeetNow", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "HideSCAMeetNow", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Disable All Balloon Notifications") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "TaskbarNoNotification", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "TaskbarNoNotification", 0);
        }
        SetExplorerRestartNeeded(true);
    }
    else if (tweak.name == "Hide Details Pane in File Explorer") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "NoPreviewPane", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "NoPreviewPane", 2);
        }
        SetExplorerRestartNeeded(true);
    }
}

// Get appearance tweaks from registry
inline std::vector<AppearanceTweak> GetAppearanceTweaks() {
    std::vector<AppearanceTweak> tweaks = {
        {
            "Disable Bing Search in Start Menu",
            "Controls whether the search box in the Windows Start menu performs Bing web searches",
            "", 
            "", 
            !AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Search", "BingSearchEnabled", 0)
        },
        {
            "Hide Personalized Web Recommendations",
            "Removes personalized website recommendations from the Start menu",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Policies\\Microsoft\\Windows\\Explorer", "HideRecommendedPersonalizedSites", 1)
        },
        {
            "Hide Recommended Section in Start Menu",
            "Completely removes the Recommended section from the Start menu",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Policies\\Microsoft\\Windows\\Explorer", "HideRecommendedSection", 1) &&
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "HideRecommendedSection", 1) &&
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "Intellimenus", 1)
        },
        {
            "Hide Clock in System Tray",
            "Hides the system clock from the taskbar notification area",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "HideClock", 1)
        },
        {
            "Hide Meet Now Icon",
            "Removes the Meet Now (instant meeting) icon from the taskbar",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "HideSCAMeetNow", 1)
        },
        {
            "Disable All Balloon Notifications",
            "Turns off all balloon notifications from the system tray",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "TaskbarNoNotification", 1)
        },
        {
            "Hide Details Pane in File Explorer",
            "Hides the details pane in File Explorer that shows file properties",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoPreviewPane", 1)
        },
        {
            "Center Taskbar Icons",
            "Controls whether taskbar icons are displayed centered or left-aligned",
            "",
            "",
            AppearanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "TaskbarAl", 1)
        },
        {
            "Enable Dark Mode",
            "Controls whether Windows uses dark theme. Applies to apps and system interface",
            "",
            "",
            AppearanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", "AppsUseLightTheme", 0)
        },
        {
            "Show Detailed BSoD",
            "Controls whether detailed technical information is displayed on blue screen errors",
            "",
            "",
            AppearanceCheckRegistryHKLM("SYSTEM\\CurrentControlSet\\Control\\CrashControl", "DisplayParameters", 1)
        },
        {
            "Enable Mouse Acceleration",
            "When enabled, cursor movement is affected by the speed of your physical mouse movements",
            "",
            "",
            AppearanceCheckRegistryStringHKCU("Control Panel\\Mouse", "MouseSpeed", "1")
        },
        {
            "Enable NumLock on Startup",
            "Controls the state of the NumLock key when your computer starts",
            "",
            "",
            AppearanceCheckRegistryUsers(".DEFAULT\\Control Panel\\Keyboard", "InitialKeyboardIndicators", "2")
        },
        {
            "Show Search Button in Taskbar",
            "When enabled, the search button is displayed in the taskbar",
            "",
            "",
            AppearanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", "SearchboxTaskbarMode", 1)
        },
        {
            "Show File Extensions",
            "When enabled, file extensions (.txt, .jpg, etc.) are made visible",
            "",
            "",
            !AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "HideFileExt", 1)
        },
        {
            "Show Hidden Files",
            "When enabled, hidden files are displayed",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Hidden", 1)
        },
        {
            "Enable Snap Assist Flyout",
            "When enabled, helper flyout is displayed when hovering screen corners or during window snapping",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "EnableSnapAssistFlyout", 1)
        },
        {
            "Enable Snap Assist Suggestion",
            "When enabled, suggestions for other apps to fill remaining areas are shown during window snapping",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "SnapAssist", 1)
        },
        {
            "Enable Snap Window",
            "When enabled, you can snap windows by dragging them to the edges of the screen",
            "",
            "",
            AppearanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "EnableSnapBar", 1)
        },
        {
            "Enable Sticky Keys",
            "When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries",
            "",
            "",
            AppearanceCheckRegistryStringHKCU("Control Panel\\Accessibility\\StickyKeys", "Flags", "510")
        },
        {
            "Show Task View Button in Taskbar",
            "When enabled, the Task View button is displayed in the taskbar",
            "",
            "",
            AppearanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowTaskViewButton", 1)
        },
        {
            "Show Verbose Messages During Logon",
            "Shows detailed messages during login process for troubleshooting and diagnostics",
            "",
            "",
            AppearanceCheckRegistryHKLM("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "VerboseStatus", 1)
        },
        {
            "Show Widgets Button in Taskbar",
            "When enabled, the Widgets button is displayed in the taskbar",
            "",
            "",
            AppearanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "TaskbarDa", 1)
        },
        {
            "Enable Classic Right-Click Menu",
            "Shows old (compact) context menu when right-clicking in file explorer on Windows 11",
            "",
            "",
            IsClassicRightClickEnabled()
        },
        {
            "Remove Gallery from Navigation Pane",
            "Removes or adds the Gallery item from the navigation pane on the left side of File Explorer",
            "",
            "",
            IsGalleryRemovedFromPane()
        }
    };
    
    return tweaks;
} 