#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "windows_utils.h" // Windows API utility functions
#include <winreg.h>
#include <sstream>
#include <powrprof.h> // Windows Power Management API

// PowerManagement fonksiyonları için DLL importları
#pragma comment(lib, "PowrProf.lib")

// CMD komutlarını gizli çalıştırmak için dışardan tanımlanan fonksiyon - Eskiden kullanılan
extern bool ExecuteCommandSilent(const char* command);

// Structure to hold performance tweak information
struct PerformanceTweak {
    std::string name;
    std::string tooltip;
    std::string enableCommand;  // Uyumluluk için tutuyoruz
    std::string disableCommand; // Uyumluluk için tutuyoruz
    bool enabled;
};

// Hem HKCU hem de HKLM'de registry değerini kontrol et
inline bool PerformanceCheckRegistry(const char* keyPath, const char* valueName, DWORD expectedValue) {
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
inline bool PerformanceCheckRegistryHKLM(const char* keyPath, const char* valueName, DWORD expectedValue) {
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
inline bool PerformanceCheckRegistryHKCU(const char* keyPath, const char* valueName, DWORD expectedValue) {
    DWORD value = 0;
    bool valueExists = WindowsUtils::GetRegistryValueDWORD(HKEY_CURRENT_USER, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// Özel string değerleri için kontrol fonksiyonu
inline bool PerformanceCheckRegistryString(const char* keyPath, const char* valueName, const char* expectedValue) {
    std::string value;
    
    // Önce HKEY_CURRENT_USER'da ara
    bool valueExists = WindowsUtils::GetRegistryValueString(HKEY_CURRENT_USER, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // HKEY_CURRENT_USER'da bulunamadıysa HKEY_LOCAL_MACHINE'de ara
    valueExists = WindowsUtils::GetRegistryValueString(HKEY_LOCAL_MACHINE, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// Servislerin durumunu kontrol et - Modern Windows API kullanarak
inline bool IsServiceDisabled(const char* serviceName) {
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager) {
        return false;
    }
    
    SC_HANDLE hService = OpenServiceA(hSCManager, serviceName, SERVICE_QUERY_STATUS | SERVICE_QUERY_CONFIG);
    if (!hService) {
        CloseServiceHandle(hSCManager);
        return false;
    }
    
    // Servis yapılandırmasını kontrol et
    DWORD bytesNeeded = 0;
    LPQUERY_SERVICE_CONFIGA pServiceConfig = NULL;
    
    // Önce gerekli bellek miktarını öğren
    if (!QueryServiceConfigA(hService, NULL, 0, &bytesNeeded) && 
        GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        
        pServiceConfig = (LPQUERY_SERVICE_CONFIGA)LocalAlloc(LPTR, bytesNeeded);
        if (pServiceConfig) {
            if (QueryServiceConfigA(hService, pServiceConfig, bytesNeeded, &bytesNeeded)) {
                // Servis durumunu kontrol et
                SERVICE_STATUS serviceStatus;
                bool isDisabled = false;
                
                if (pServiceConfig->dwStartType == SERVICE_DISABLED) {
                    isDisabled = true;
                } 
                
                LocalFree(pServiceConfig);
                CloseServiceHandle(hService);
                CloseServiceHandle(hSCManager);
                return isDisabled;
            }
            LocalFree(pServiceConfig);
        }
    }
    
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return false;
}

// Ultimate Performance güç planının etkin olup olmadığını kontrol et
inline bool IsUltimatePerformanceEnabled() {
    bool result = false;
    
    // Registry üzerinden güç planını kontrol et
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
                     "SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes", 
                     0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        
        // Aktif güç planı GUID'i al
        char activeSchemeGuid[40] = {0};
        DWORD activeSchemeSize = sizeof(activeSchemeGuid);
        
        if (RegGetValueA(HKEY_LOCAL_MACHINE, 
                        "SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes", 
                        "ActivePowerScheme", RRF_RT_REG_SZ, NULL, 
                        activeSchemeGuid, &activeSchemeSize) == ERROR_SUCCESS) {
            
            // Aktif GUID altında adı kontrol et
            std::string schemePath = std::string("SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes\\") + activeSchemeGuid;
            char schemeName[256] = {0};
            DWORD nameSize = sizeof(schemeName);
            
            if (RegGetValueA(HKEY_LOCAL_MACHINE, schemePath.c_str(), 
                            "FriendlyName", RRF_RT_REG_SZ, NULL, 
                            schemeName, &nameSize) == ERROR_SUCCESS) {
                // Ultimate Performance ifadesini ara
                if (strstr(schemeName, "Ultimate Performance") != nullptr) {
                    result = true;
                }
            }
        }
        
        RegCloseKey(hKey);
    }
    
    return result;
}

// Hibernasyon devre dışı mı kontrol et
inline bool IsHibernationDisabled() {
    SYSTEM_POWER_STATUS powerStatus;
    if (GetSystemPowerStatus(&powerStatus)) {
        // Sistemde hibernasyon desteği var mı kontrol et
        DWORD hibernateEnabled = 0;
        DWORD bufferSize = sizeof(hibernateEnabled);
        
        // Hibernasyon durumunu registry'den kontrol et
        HKEY hKey;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
                         "SYSTEM\\CurrentControlSet\\Control\\Power", 
                         0, KEY_READ, &hKey) == ERROR_SUCCESS) {
            
            if (RegQueryValueExA(hKey, "HibernateEnabled", NULL, NULL, 
                               (LPBYTE)&hibernateEnabled, &bufferSize) == ERROR_SUCCESS) {
                RegCloseKey(hKey);
                return (hibernateEnabled == 0); // 0 ise devre dışı
            }
            
            RegCloseKey(hKey);
        }
    }
    
    // Hata durumunda varsayılan olarak etkin kabul et (devre dışı değil)
    return false;
}

// Hibernasyon dosyasını kontrol et ve ayarla - güvenli CreateProcess ile
inline void SetHibernationFile(bool disable) {
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    
    char cmdLine[256];
    if (disable) {
        strcpy_s(cmdLine, sizeof(cmdLine), "powercfg.exe /hibernate off");
    } else {
        strcpy_s(cmdLine, sizeof(cmdLine), "powercfg.exe /hibernate on");
    }
    
    if (CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, 
                     CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

// Apply performance tweak using WindowsUtils API
inline void ApplyPerformanceTweak(PerformanceTweak& tweak) {
    if (tweak.name == "Disable Fullscreen Optimizations") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "System\\GameConfigStore", 
                "GameDVR_DXGIHonorFSEWindowsCompatible", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "System\\GameConfigStore", 
                "GameDVR_DXGIHonorFSEWindowsCompatible", 0);
        }
    }
    else if (tweak.name == "Disable Mouse Acceleration") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseSpeed", "0");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold1", "0");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold2", "0");
        } else {
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseSpeed", "1");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold1", "6");
            WindowsUtils::SetRegistryValueString(HKEY_CURRENT_USER, 
                "Control Panel\\Mouse", "MouseThreshold2", "10");
        }
    }
    else if (tweak.name == "Disable Game Bar") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR", 
                "AllowGameDVR", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\GameDVR", 
                "AppCaptureEnabled", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\GameBar", 
                "UseNexusForGameBarEnabled", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\GameBar", 
                "ShowStartupPanel", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\GameBar", 
                "UseNexusForGameBarEnabled", 1);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\GameBar", 
                "ShowStartupPanel", 1);
        }
    }
    else if (tweak.name == "Disable Game Mode") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\GameDVR", 
                "AutoGameModeEnabled", 0);
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\GameBar", 
                "AutoGameModeEnabled", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\GameBar", 
                "AutoGameModeEnabled", 1);
        }
    }
    else if (tweak.name == "Activate Ultimate Performance Mode") {
        if (tweak.enabled) {
            // Önce Ultimate Performance planını oluştur/etkinleştir
            // Komut satırı ile yapmalıyız - API ile direkt yapılamıyor
            STARTUPINFOA si = { sizeof(STARTUPINFOA) };
            PROCESS_INFORMATION pi;
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_HIDE;
            
            // İki adımda yapalım:
            // 1. Ultimate Performance planını oluştur
            char cmdLine1[256];
            strcpy_s(cmdLine1, sizeof(cmdLine1), "powercfg.exe -duplicatescheme e9a42b02-d5df-448d-aa00-03f14749eb61");
            
            if (CreateProcessA(NULL, cmdLine1, NULL, NULL, FALSE, 
                             CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
                WaitForSingleObject(pi.hProcess, INFINITE);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }
            
            // 2. Ultimate Performance planını etkinleştir
            // Önce planın GUID'ini bul
            HKEY hKey;
            if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
                            "SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes", 
                            0, KEY_READ, &hKey) == ERROR_SUCCESS) {
                
                char buffer[256];
                DWORD bufferSize = sizeof(buffer);
                DWORD index = 0;
                std::string ultimateGuid;
                
                // Tüm güç planlarını döngüye al
                while (RegEnumKeyExA(hKey, index, buffer, &bufferSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
                    // Her bir güç planı anahtarını aç
                    std::string keyPath = std::string("SYSTEM\\CurrentControlSet\\Control\\Power\\User\\PowerSchemes\\") + buffer;
                    char friendlyName[256];
                    DWORD nameSize = sizeof(friendlyName);
                    
                    // Güç planı adını oku
                    if (RegGetValueA(HKEY_LOCAL_MACHINE, keyPath.c_str(), 
                                    "FriendlyName", RRF_RT_REG_SZ, NULL, 
                                    friendlyName, &nameSize) == ERROR_SUCCESS) {
                        if (strstr(friendlyName, "Ultimate Performance") != nullptr) {
                            ultimateGuid = buffer;
                            break;
                        }
                    }
                    
                    index++;
                    bufferSize = sizeof(buffer);
                }
                
                RegCloseKey(hKey);
                
                // Eğer Ultimate Performance GUID'i bulunduysa, etkinleştir
                if (!ultimateGuid.empty()) {
                    char cmdLine2[256];
                    std::string cmd = std::string("powercfg.exe -setactive ") + ultimateGuid;
                    strcpy_s(cmdLine2, sizeof(cmdLine2), cmd.c_str());
                    
                    if (CreateProcessA(NULL, cmdLine2, NULL, NULL, FALSE, 
                                     CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
                        WaitForSingleObject(pi.hProcess, INFINITE);
                        CloseHandle(pi.hProcess);
                        CloseHandle(pi.hThread);
                    }
                }
                // GUID bulunamadıysa, dengeli profil oluştur ve etkinleştir 
                else {
                    // Yüksek performans planını etkinleştir 
                    char cmdLine2[256];
                    strcpy_s(cmdLine2, sizeof(cmdLine2), "powercfg.exe -setactive 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c");
                    
                    if (CreateProcessA(NULL, cmdLine2, NULL, NULL, FALSE, 
                                     CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
                        WaitForSingleObject(pi.hProcess, INFINITE);
                        CloseHandle(pi.hProcess);
                        CloseHandle(pi.hThread);
                    }
                }
            }
        } else {
            // Dengeli güç planına geri dön 
            STARTUPINFOA si = { sizeof(STARTUPINFOA) };
            PROCESS_INFORMATION pi;
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_HIDE;
            
            char cmdLine[256];
            strcpy_s(cmdLine, sizeof(cmdLine), "powercfg.exe -setactive 381b4222-f694-41f0-9685-ff5bb260df2e");
            
            if (CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, 
                             CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
                WaitForSingleObject(pi.hProcess, INFINITE);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }
        }
    }
    else if (tweak.name == "Disable Hardware Accelerated GPU Scheduling") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", 
                "HwSchMode", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", 
                "HwSchMode", 2);
        }
    }
    else if (tweak.name == "Limit Windows Defender Usage") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Scan", 
                "AvgCPULoadFactor", 25);
        } else {
            WindowsUtils::DeleteRegistryValue(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Scan", 
                "AvgCPULoadFactor");
        }
    }
    else if (tweak.name == "Disable Core Isolation") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceGuard\\Scenarios\\HypervisorEnforcedCodeIntegrity", 
                "Enabled", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceGuard\\Scenarios\\HypervisorEnforcedCodeIntegrity", 
                "Enabled", 1);
        }
    }
    else if (tweak.name == "Disable Prefetch") {
        if (tweak.enabled) {
            // Windows API kullan
            WindowsUtils::StopService("SysMain");
            WindowsUtils::ConfigureService("SysMain", SERVICE_DISABLED);
        } else {
            WindowsUtils::ConfigureService("SysMain", SERVICE_AUTO_START);
            WindowsUtils::StartService("SysMain");
        }
    }
    else if (tweak.name == "Disable Storage Sense") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\StorageSense\\Parameters\\StoragePolicy", 
                "01", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\StorageSense\\Parameters\\StoragePolicy", 
                "01", 1);
        }
    }
    else if (tweak.name == "Disable Windows Search") {
        if (tweak.enabled) {
            WindowsUtils::StopService("wsearch");
            WindowsUtils::ConfigureService("wsearch", SERVICE_DISABLED);
        } else {
            WindowsUtils::ConfigureService("wsearch", SERVICE_AUTO_START);
            WindowsUtils::StartService("wsearch");
        }
    }
    else if (tweak.name == "Disable Hibernation") {
        // Windows API kullanarak hibernasyon özelliğini devre dışı bırak
        HKEY hKey;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
                         "SYSTEM\\CurrentControlSet\\Control\\Power", 
                         0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
            
            DWORD hibernateEnabled = tweak.enabled ? 0 : 1; // 0 = devre dışı, 1 = etkin
            RegSetValueExA(hKey, "HibernateEnabled", 0, REG_DWORD, 
                          (const BYTE*)&hibernateEnabled, sizeof(hibernateEnabled));
            
            RegCloseKey(hKey);
            
            // Hibernasyon dosyasını ayarla (güvenli şekilde)
            SetHibernationFile(tweak.enabled);
        }
    }
    else if (tweak.name == "Enable Confirm File Delete Dialog") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
            "ConfirmFileDelete", tweak.enabled ? 1 : 0);
    }
    else if (tweak.name == "Permanently Delete Files (Skip Recycle Bin)") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
            "NoRecycleFiles", tweak.enabled ? 1 : 0);
    }
}

// Get performance tweaks from registry
inline std::vector<PerformanceTweak> GetPerformanceTweaks() {
    const std::string cur_ver = "Software\\Microsoft\\Windows\\CurrentVersion\\";
    
    std::vector<PerformanceTweak> tweaks = {
        {
            "Disable Fullscreen Optimizations",
            "Disables Windows fullscreen optimizations for better game performance",
            "", 
            "", 
            PerformanceCheckRegistryHKCU("System\\GameConfigStore", "GameDVR_DXGIHonorFSEWindowsCompatible", 1)
        },
        {
            "Disable Mouse Acceleration",
            "Removes mouse acceleration for more consistent cursor movement",
            "",
            "",
            PerformanceCheckRegistryString("Control Panel\\Mouse", "MouseSpeed", "0") &&
            PerformanceCheckRegistryString("Control Panel\\Mouse", "MouseThreshold1", "0") &&
            PerformanceCheckRegistryString("Control Panel\\Mouse", "MouseThreshold2", "0")
        },
        {
            "Disable Game Bar",
            "Disables Game Bar and related features to reduce overhead",
            "",
            "",
            PerformanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\GameBar", "UseNexusForGameBarEnabled", 0) &&
            PerformanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\GameBar", "ShowStartupPanel", 0) 
        },
        {
            "Disable Game Mode",
            "Turns off Windows Game Mode which can cause issues with some games",
            "",
            "",
            PerformanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\GameBar", "AutoGameModeEnabled", 0)
        },
        {
            "Activate Ultimate Performance Mode",
            "Activates the hidden Ultimate Performance power plan for maximum performance",
            "",
            "",
            IsUltimatePerformanceEnabled()
        },
        {
            "Disable Hardware Accelerated GPU Scheduling",
            "Disables HAGS which can cause issues with some systems",
            "",
            "",
            PerformanceCheckRegistryHKLM("SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", "HwSchMode", 1)
        },
        {
            "Limit Windows Defender Usage",
            "Limits Windows Defender CPU usage for better performance",
            "",
            "",
            PerformanceCheckRegistryHKLM("SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Scan", "AvgCPULoadFactor", 25)
        },
        {
            "Disable Core Isolation",
            "Disables memory integrity for better performance (reduces security)",
            "",
            "",
            PerformanceCheckRegistryHKLM("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeviceGuard\\Scenarios\\HypervisorEnforcedCodeIntegrity", "Enabled", 0)
        },
        {
            "Disable Prefetch",
            "Disables Windows Prefetch service to free up resources",
            "",
            "",
            IsServiceDisabled("SysMain")
        },
        {
            "Disable Storage Sense",
            "Disables automatic disk cleanup to prevent background disk activity",
            "",
            "",
            PerformanceCheckRegistryHKCU("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\StorageSense\\Parameters\\StoragePolicy", "01", 0)
        },
        {
            "Disable Windows Search",
            "Disables Windows Search indexing service to free up system resources",
            "",
            "",
            IsServiceDisabled("wsearch")
        },
        {
            "Disable Hibernation",
            "Disables system hibernation to free up disk space and resources",
            "",
            "",
            IsHibernationDisabled()
        },
        {
            "Enable Confirm File Delete Dialog",
            "Shows a confirmation dialog when deleting files",
            "",
            "",
            PerformanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "ConfirmFileDelete", 1)
        },
        {
            "Permanently Delete Files (Skip Recycle Bin)",
            "Deletes files permanently without moving them to the Recycle Bin",
            "",
            "",
            PerformanceCheckRegistryHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoRecycleFiles", 1)
        }
    };
    
    return tweaks;
} 