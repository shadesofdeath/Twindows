#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "windows_utils.h" // Windows API utility functions

// CMD komutlarını gizli çalıştırmak için dışardan tanımlanan fonksiyon - Eskiden kullanılan
extern bool ExecuteCommandSilent(const char* command);

// Structure to hold security tweak information
struct SecurityTweak {
    std::string name;
    std::string tooltip;
    std::string enableCommand;  // Uyumluluk için tutuyoruz
    std::string disableCommand; // Uyumluluk için tutuyoruz
    bool enabled;
};

// Registry ayarını DWORD olarak kontrol et
inline bool CheckSecuritySettingDWORD(const char* keyPath, const char* valueName, DWORD checkValue, HKEY rootKey = HKEY_LOCAL_MACHINE) {
    DWORD value = 0;
    bool valueExists = WindowsUtils::GetRegistryValueDWORD(rootKey, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == checkValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// Registry ayarını String olarak kontrol et
inline bool CheckSecuritySettingString(const char* keyPath, const char* valueName, const char* checkValue, HKEY rootKey = HKEY_LOCAL_MACHINE) {
    std::string value;
    bool valueExists = WindowsUtils::GetRegistryValueString(rootKey, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == checkValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// Windows Defender durumunu kontrol et - Windows API kullanarak
inline bool IsDefenderEnabled() {
    // Windows Defender durumunu registry üzerinden kontrol et
    HKEY hKey;
    DWORD value = 0;
    DWORD dataSize = sizeof(DWORD);
    bool isEnabled = true; // Varsayılan olarak etkin varsayalım

    // HKLM\SOFTWARE\Microsoft\Windows Defender\Real-Time Protection
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
                     "SOFTWARE\\Microsoft\\Windows Defender\\Real-Time Protection", 
                     0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, "DisableRealtimeMonitoring", 0, NULL, 
                            (LPBYTE)&value, &dataSize) == ERROR_SUCCESS) {
            isEnabled = (value == 0); // 0 = Enabled, 1 = Disabled
        }
        RegCloseKey(hKey);
    }
    
    return isEnabled;
}

// Servis durumunu kontrol et
inline bool IsServiceEnabled(const char* serviceName) {
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager) {
        return false;
    }
    
    SC_HANDLE hService = OpenServiceA(hSCManager, serviceName, SERVICE_QUERY_STATUS);
    if (!hService) {
        CloseServiceHandle(hSCManager);
        return false;
    }
    
    SERVICE_STATUS serviceStatus;
    BOOL success = QueryServiceStatus(hService, &serviceStatus);
    
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    
    if (success == TRUE) {
        return (serviceStatus.dwCurrentState == SERVICE_RUNNING);
    }
    
    return false;
}

// Registry anahtarı var mı kontrol et
inline bool DoesRegistryKeyExist(const char* keyPath, HKEY rootKey = HKEY_LOCAL_MACHINE) {
    HKEY hKey;
    LONG result = RegOpenKeyExA(rootKey, keyPath, 0, KEY_READ, &hKey);
    
    if (result == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return true;
    }
    
    return false;
}

// Güvenlik ayarlarını uygula
inline void ApplySecurityTweak(SecurityTweak& tweak) {
    // Windows Defender ile ilgili ayarlar
    if (tweak.name == "Windows Defender'ı Etkinleştir") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Defender", 
                "DisableAntiSpyware", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Defender", 
                "DisableAntiSpyware", 1);
        }
    }
    else if (tweak.name == "Gerçek Zamanlı Korumayı Etkinleştir") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", 
                "DisableRealtimeMonitoring", 0);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", 
                "DisableRealtimeMonitoring", 1);
        }
    }
    else if (tweak.name == "SmartScreen'i Etkinleştir") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\System", 
                "EnableSmartScreen", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\System", 
                "EnableSmartScreen", 0);
        }
    }
    else if (tweak.name == "Windows Güvenlik Duvarını Etkinleştir") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile", 
                "EnableFirewall", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile", 
                "EnableFirewall", 0);
        }
    }
    // UAC ve Oturum Güvenliği
    else if (tweak.name == "UAC'yi Etkinleştir") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "EnableLUA", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "EnableLUA", 0);
        }
    }
    else if (tweak.name == "UAC Seviyesini Yükselt") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "ConsentPromptBehaviorAdmin", 2);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "ConsentPromptBehaviorAdmin", 0);
        }
    }
    else if (tweak.name == "Güvenli Masaüstünde UAC'yi Etkinleştir") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "PromptOnSecureDesktop", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "PromptOnSecureDesktop", 0);
        }
    }
    else if (tweak.name == "Son Kullanıcı Adını Gizle") {
        if (tweak.enabled) {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "DontDisplayLastUserName", 1);
        } else {
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 
                "DontDisplayLastUserName", 0);
        }
    }
    // SMB ve Ağ Güvenliği
    else if (tweak.name == "SMB1 Protokolünü Devre Dışı Bırak") {
        if (tweak.enabled) { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\LanmanServer\\Parameters", 
                "SMB1", 0);
        } else { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\LanmanServer\\Parameters", 
                "SMB1", 1);
        }
    }
    else if (tweak.name == "LLMNR Protokolünü Devre Dışı Bırak") {
        if (tweak.enabled) { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows NT\\DNSClient", 
                "EnableMulticast", 0);
        } else { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows NT\\DNSClient", 
                "EnableMulticast", 1);
        }
    }
    else if (tweak.name == "NBT-NS'yi Devre Dışı Bırak") {
        if (tweak.enabled) { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\NetBT\\Parameters", 
                "NodeType", 2);
        } else { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\NetBT\\Parameters", 
                "NodeType", 1);
        }
    }
    // Uzak Erişim Güvenliği
    else if (tweak.name == "Uzak Masaüstü Güvenlik Seviyesini Yükselt") {
        if (tweak.enabled) { // Yükseltme
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 
                "SecurityLayer", 2);
        } else { // Düşürme
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 
                "SecurityLayer", 0);
        }
    }
    else if (tweak.name == "RDP için NLA Kimlik Doğrulamasını Etkinleştir") {
        if (tweak.enabled) { // NLA açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 
                "UserAuthentication", 1);
        } else { // NLA kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 
                "UserAuthentication", 0);
        }
    }
    else if (tweak.name == "RDP Şifreleme Seviyesini Yükselt") {
        if (tweak.enabled) { // Yükseltme
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 
                "MinEncryptionLevel", 3);
        } else { // Düşürme
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", 
                "MinEncryptionLevel", 1);
        }
    }
    // AutoRun ve Çıkarılabilir Medya Güvenliği
    else if (tweak.name == "AutoRun'u Devre Dışı Bırak") {
        if (tweak.enabled) { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "NoDriveTypeAutoRun", 255);
        } else { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
                "NoDriveTypeAutoRun", 0);
        }
    }
    else if (tweak.name == "USB Depolamayı Etkinleştir") {
        if (tweak.enabled) { // Etkinleştirme
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\USBSTOR", 
                "Start", 3);
        } else { // Devre dışı bırakma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SYSTEM\\CurrentControlSet\\Services\\USBSTOR", 
                "Start", 4);
        }
    }
    // PowerShell ve Komut Dosyası Güvenliği
    else if (tweak.name == "PowerShell Yürütme İlkesini Güvenli Yap") {
        if (tweak.enabled) { // RemoteSigned yapma
            WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\PowerShell", 
                "ExecutionPolicy", "RemoteSigned");
        } else { // Kısıtlamaları kaldırma
            WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\PowerShell", 
                "ExecutionPolicy", "Unrestricted");
        }
    }
    else if (tweak.name == "PowerShell Komut Kaydetmeyi Etkinleştir") {
        if (tweak.enabled) { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\PowerShell", 
                "EnableScriptBlockLogging", 1);
        } else { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\PowerShell", 
                "EnableScriptBlockLogging", 0);
        }
    }
    else if (tweak.name == "Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir") {
        if (tweak.enabled) { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Script Host\\Settings", 
                "Enabled", 0);
        } else { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows Script Host\\Settings", 
                "Enabled", 1);
        }
    }
    // Güncelleştirme Güvenliği
    else if (tweak.name == "Windows Update'i Etkinleştir") {
        if (tweak.enabled) { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", 
                "NoAutoUpdate", 0);
        } else { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", 
                "NoAutoUpdate", 1);
        }
    }
    else if (tweak.name == "Otomatik Güncellemeleri Etkinleştir") {
        if (tweak.enabled) { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", 
                "AUOptions", 4);
        } else { // Elle güncelleme
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", 
                "AUOptions", 2);
        }
    }
    // Diğer Güvenlik Ayarları
    else if (tweak.name == "WPAD Protokolünü Devre Dışı Bırak") {
        if (tweak.enabled) { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Wpad", 
                "WpadOverride", 1);
        } else { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
                "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Wpad", 
                "WpadOverride", 0);
        }
    }
    else if (tweak.name == "WinRM Şifresiz Trafiği Devre Dışı Bırak") {
        if (tweak.enabled) { // Kapatma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\WinRM\\Service", 
                "AllowUnencryptedTraffic", 0);
        } else { // Açma
            WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
                "SOFTWARE\\Policies\\Microsoft\\Windows\\WinRM\\Service", 
                "AllowUnencryptedTraffic", 1);
        }
    }
}

// Tüm güvenlik ayarlarını al
inline std::vector<SecurityTweak> GetSecurityTweaks() {
    std::vector<SecurityTweak> tweaks = {
        // Windows Defender
        {
            "Windows Defender'ı Etkinleştir",
            "Windows Defender antivirüs servisi",
            "",
            "",
            !CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows Defender", "DisableAntiSpyware", 1)
        },
        {
            "Gerçek Zamanlı Korumayı Etkinleştir",
            "Windows Defender'ın gerçek zamanlı koruma özelliği",
            "",
            "",
            !CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection", "DisableRealtimeMonitoring", 1)
        },
        {
            "SmartScreen'i Etkinleştir",
            "Microsoft SmartScreen filtreleme özelliği",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows\\System", "EnableSmartScreen", 1)
        },
        {
            "Windows Güvenlik Duvarını Etkinleştir",
            "Windows Güvenlik Duvarı servisi",
            "",
            "",
            CheckSecuritySettingDWORD("SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile", "EnableFirewall", 1)
        },
        
        // UAC ve Oturum Güvenliği
        {
            "UAC'yi Etkinleştir",
            "Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "EnableLUA", 1)
        },
        {
            "UAC Seviyesini Yükselt",
            "UAC seviyesini yüksek ayara getirir",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "ConsentPromptBehaviorAdmin", 2)
        },
        {
            "Güvenli Masaüstünde UAC'yi Etkinleştir",
            "UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "PromptOnSecureDesktop", 1)
        },
        {
            "Son Kullanıcı Adını Gizle",
            "Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "DontDisplayLastUserName", 1)
        },
        
        // SMB ve Ağ Güvenliği
        {
            "SMB1 Protokolünü Devre Dışı Bırak",
            "Güvenlik açığı bulunan eski SMB1 protokolünü kapatır",
            "",
            "",
            !CheckSecuritySettingDWORD("SYSTEM\\CurrentControlSet\\Services\\LanmanServer\\Parameters", "SMB1", 1)
        },
        {
            "LLMNR Protokolünü Devre Dışı Bırak",
            "Link-Local Multicast Name Resolution protokolünü devre dışı bırakır",
            "",
            "",
            !CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows NT\\DNSClient", "EnableMulticast", 1)
        },
        {
            "NBT-NS'yi Devre Dışı Bırak",
            "NetBIOS Name Service protokolünü devre dışı bırakır",
            "",
            "",
            CheckSecuritySettingDWORD("SYSTEM\\CurrentControlSet\\Services\\NetBT\\Parameters", "NodeType", 2)
        },
        
        // Uzak Erişim Güvenliği
        {
            "Uzak Masaüstü Güvenlik Seviyesini Yükselt",
            "Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar",
            "",
            "",
            CheckSecuritySettingDWORD("SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", "SecurityLayer", 2)
        },
        {
            "RDP için NLA Kimlik Doğrulamasını Etkinleştir",
            "RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir",
            "",
            "",
            CheckSecuritySettingDWORD("SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", "UserAuthentication", 1)
        },
        {
            "RDP Şifreleme Seviyesini Yükselt",
            "RDP için şifreleme seviyesini yüksek olarak ayarlar",
            "",
            "",
            CheckSecuritySettingDWORD("SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp", "MinEncryptionLevel", 3)
        },
        
        // AutoRun ve Çıkarılabilir Medya Güvenliği
        {
            "AutoRun'u Devre Dışı Bırak",
            "Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "NoDriveTypeAutoRun", 255)
        },
        {
            "USB Depolamayı Etkinleştir",
            "USB depolama cihazlarını etkinleştirir veya devre dışı bırakır",
            "",
            "",
            CheckSecuritySettingDWORD("SYSTEM\\CurrentControlSet\\Services\\USBSTOR", "Start", 3)
        },
        
        // PowerShell ve Komut Dosyası Güvenliği
        {
            "PowerShell Yürütme İlkesini Güvenli Yap",
            "PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar",
            "",
            "",
            CheckSecuritySettingString("SOFTWARE\\Policies\\Microsoft\\Windows\\PowerShell", "ExecutionPolicy", "RemoteSigned")
        },
        {
            "PowerShell Komut Kaydetmeyi Etkinleştir",
            "PowerShell komut blokları için günlük kaydını etkinleştirir",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows\\PowerShell", "EnableScriptBlockLogging", 1)
        },
        {
            "Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir",
            "Windows Script Host güvenliğini etkinleştirir",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows Script Host\\Settings", "Enabled", 0)
        },
        
        // Güncelleştirme Güvenliği
        {
            "Windows Update'i Etkinleştir",
            "Windows Update servisini etkinleştirir",
            "",
            "",
            !CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "NoAutoUpdate", 1)
        },
        {
            "Otomatik Güncellemeleri Etkinleştir",
            "Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "AUOptions", 4)
        },
        
        // Diğer Güvenlik Ayarları
        {
            "WPAD Protokolünü Devre Dışı Bırak",
            "Web Proxy Auto-Discovery protokolünü devre dışı bırakır",
            "",
            "",
            CheckSecuritySettingDWORD(
                "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Wpad", 
                "WpadOverride", 1, HKEY_CURRENT_USER)
        },
        {
            "WinRM Şifresiz Trafiği Devre Dışı Bırak",
            "Windows Remote Management için şifresiz trafiği engeller",
            "",
            "",
            CheckSecuritySettingDWORD("SOFTWARE\\Policies\\Microsoft\\Windows\\WinRM\\Service", "AllowUnencryptedTraffic", 0)
        }
    };
    
    return tweaks;
} 