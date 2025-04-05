#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "windows_utils.h" // Windows API utility functions

// CMD komutlarını gizli çalıştırmak için dışardan tanımlanan fonksiyon - Eskiden kullanılan
extern bool ExecuteCommandSilent(const char* command);

struct PrivacyTweak {
    std::string name;
    std::string tooltip;
    std::string regCommand; // Uyumluluk için tutuyoruz
    bool enabled;
};

// Kayıtlı ayarları okuyarak başlangıç durumlarını belirle - düzeltilmiş versiyon
inline bool IsRegistryKeyEnabled(const char* keyPath, const char* valueName, DWORD expectedValue) {
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

// HKEY_LOCAL_MACHINE anahtarları için özel kontrol fonksiyonu
inline bool IsRegistryKeyEnabledHKLM(const char* keyPath, const char* valueName, DWORD expectedValue) {
    DWORD value = 0;
    bool valueExists = WindowsUtils::GetRegistryValueDWORD(HKEY_LOCAL_MACHINE, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

// Özel string değerleri için kontrol fonksiyonu
inline bool IsRegistryStringEnabled(const char* keyPath, const char* valueName, const char* expectedValue) {
    std::string value;
    // Önce HKEY_LOCAL_MACHINE'de ara (çoğu izin ayarı burada)
    bool valueExists = WindowsUtils::GetRegistryValueString(HKEY_LOCAL_MACHINE, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // HKEY_LOCAL_MACHINE'de bulunamadıysa HKEY_CURRENT_USER'da ara
    valueExists = WindowsUtils::GetRegistryValueString(HKEY_CURRENT_USER, keyPath, valueName, value);
    
    // Değer mevcutsa, beklenen değerle karşılaştır
    if (valueExists) {
        return value == expectedValue;
    }
    
    // Değer yoksa varsayılan olarak devre dışı kabul et
    return false;
}

inline std::vector<PrivacyTweak> GetPrivacyTweaks() {
    const std::string cur_ver = "Software\\Microsoft\\Windows\\CurrentVersion\\";
    
    std::vector<PrivacyTweak> tweaks = {
        {
            "Disable Sync Provider Notifications in File Explorer",
            "Disables file sync provider notifications in File Explorer",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "Explorer\\Advanced").c_str(), "ShowSyncProviderNotifications", 0)
        },
        {
            "Clear Recent Files on Exit",
            "Clears the list of recently opened files when you exit Windows",
            "",
            IsRegistryKeyEnabled("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", "ClearRecentDocsOnExit", 1)
        },
        {
            "Disable Windows Copilot",
            "Disables Windows Copilot AI assistant",
            "",
            IsRegistryKeyEnabled("SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsCopilot", "TurnOffWindowsCopilot", 1)
        },
        {
            "Disable Fun Facts and Tips on Lock Screen",
            "Disables fun facts, tips, tricks on your lock screen",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "ContentDeliveryManager").c_str(), "RotatingLockScreenOverlayEnabled", 0) &&
            IsRegistryKeyEnabled(std::string(cur_ver + "ContentDeliveryManager").c_str(), "SubscribedContent-338387Enabled", 0)
        },
        {
            "Disable Suggested Content in Settings",
            "Disables suggested content in the Settings app",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "ContentDeliveryManager").c_str(), "SubscribedContent-338393Enabled", 0) &&
            IsRegistryKeyEnabled(std::string(cur_ver + "ContentDeliveryManager").c_str(), "SubscribedContent-353694Enabled", 0) &&
            IsRegistryKeyEnabled(std::string(cur_ver + "ContentDeliveryManager").c_str(), "SubscribedContent-353696Enabled", 0)
        },
        {
            "Disable Tips and Suggestions When Using Windows",
            "Disables tips and suggestions when using Windows",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "ContentDeliveryManager").c_str(), "SubscribedContent-338389Enabled", 0)
        },
        {
            "Disable 'Get the Most out of Windows' Suggestions",
            "Disables suggestions on how to get the most out of Windows and finish setting up the device",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "UserProfileEngagement").c_str(), "ScoobeSystemSettingEnabled", 0)
        },
        {
            "Disable Windows Welcome Experience",
            "Disables the Windows welcome experience after updates and when signing in",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "ContentDeliveryManager").c_str(), "SubscribedContent-310093Enabled", 0)
        },
        {
            "Disable Personalized Ads",
            "Prevents apps from showing personalized ads by using your advertising ID",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "AdvertisingInfo").c_str(), "Enabled", 0)
        },
        {
            "Disable Tailored Experiences",
            "Disables tailored experiences with diagnostic data",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "Privacy").c_str(), "TailoredExperiencesWithDiagnosticDataEnabled", 0)
        },
        {
            "Disable Recommendations in Start Menu",
            "Disables recommendations for tips, shortcuts, new apps, and more in Start menu",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "Explorer\\Advanced").c_str(), "Start_IrisRecommendations", 0)
        },
        {
            "Disable Notification Suggestions",
            "Disables notification suggestions about unused apps",
            "",
            IsRegistryKeyEnabled(std::string(cur_ver + "Notifications\\Settings\\Windows.ActionCenter.SmartOptOut").c_str(), "Enabled", 0)
        },
        {
            "Disable Bing Results in Windows Search",
            "Disables Bing results, Cortana and location search in Windows Search and search box suggestions",
            "",
            IsRegistryKeyEnabled("Software\\Policies\\Microsoft\\Windows\\Explorer", "DisableSearchBoxSuggestions", 1) &&
            IsRegistryKeyEnabled("Software\\Policies\\Microsoft\\Windows", "DisableSearchBoxSuggestions", 1) &&
            IsRegistryKeyEnabled(std::string(cur_ver + "Search").c_str(), "BingSearchEnabled", 0) &&
            IsRegistryKeyEnabled(std::string(cur_ver + "Search").c_str(), "CortanaConsent", 0) &&
            IsRegistryKeyEnabled(std::string(cur_ver + "Search").c_str(), "AllowSearchToUseLocation", 0)
        },
        {
            "Disable Edge Desktop Search Widget",
            "Disables the Edge search widget on desktop",
            "",
            IsRegistryKeyEnabled("Software\\Policies\\Microsoft\\Edge", "WebWidgetAllowed", 0)
        },
        {
            "Disable Location Access",
            "Prevents apps from accessing your location",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location", "Value", "Deny")
        },
        {
            "Disable Camera Access",
            "Prevents apps from accessing your camera",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\webcam", "Value", "Deny")
        },
        {
            "Disable Microphone Access",
            "Prevents apps from accessing your microphone",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\microphone", "Value", "Deny")
        },
        {
            "Disable Documents Library Access",
            "Prevents apps from accessing your documents library",
            "",
            IsRegistryStringEnabled("Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\documentsLibrary", "Value", "Deny")
        },
        {
            "Disable Pictures Library Access",
            "Prevents apps from accessing your pictures library",
            "",
            IsRegistryStringEnabled("Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\picturesLibrary", "Value", "Deny")
        },
        {
            "Disable Videos Library Access",
            "Prevents apps from accessing your videos library",
            "",
            IsRegistryStringEnabled("Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\videosLibrary", "Value", "Deny")
        },
        {
            "Disable Broad File System Access",
            "Prevents apps from accessing the file system broadly",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\broadFileSystemAccess", "Value", "Deny")
        },
        {
            "Disable Account Information Access",
            "Prevents apps from accessing your account information",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userAccountInformation", "Value", "Deny")
        },
        {
            "Disable Contacts Access",
            "Prevents apps from accessing your contacts",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\contacts", "Value", "Deny")
        },
        {
            "Disable Call History Access",
            "Prevents apps from accessing your call history",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\phoneCallHistory", "Value", "Deny")
        },
        {
            "Disable Messaging Access",
            "Prevents apps from accessing your messages",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\chat", "Value", "Deny")
        },
        {
            "Disable Notification Access",
            "Prevents apps from accessing your notifications",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userNotificationListener", "Value", "Deny")
        },
        {
            "Disable Email Access",
            "Prevents apps from accessing your email",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\email", "Value", "Deny")
        },
        {
            "Disable Tasks Access",
            "Prevents apps from accessing your user data tasks",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userDataTasks", "Value", "Deny")
        },
        {
            "Disable Diagnostics Access",
            "Prevents apps from accessing your diagnostic information",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\appDiagnostics", "Value", "Deny")
        },
        {
            "Disable Voice Activation",
            "Disables voice activation for all apps",
            "",
            IsRegistryKeyEnabled("Software\\Microsoft\\Speech_OneCore\\Settings\\VoiceActivation\\UserPreferenceForAllApps", "AgentActivationEnabled", 0)
        },
        {
            "Disable Calendar Access",
            "Prevents apps from accessing your calendar appointments",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\appointments", "Value", "Deny")
        },
        {
            "Disable Motion Access",
            "Prevents apps from accessing motion data",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\activity", "Value", "Deny")
        },
        {
            "Disable Radio Access",
            "Prevents apps from accessing radio controls",
            "",
            IsRegistryStringEnabled("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\radios", "Value", "Deny")
        },
        {
            "Disable Activity Feed",
            "Disables the Windows activity feed",
            "",
            IsRegistryKeyEnabledHKLM("SOFTWARE\\Policies\\Microsoft\\Windows\\System", "EnableActivityFeed", 0)
        },
        {
            "Disable Notification Center",
            "Disables the Windows notification center",
            "",
            IsRegistryKeyEnabled("Software\\Policies\\Microsoft\\Windows\\Explorer", "DisableNotificationCenter", 1) &&
            IsRegistryKeyEnabled("Software\\Microsoft\\Windows\\CurrentVersion\\PushNotifications", "ToastEnabled", 0)
        },
        {
            "Disable Xbox Screen Recording",
            "Disables the Xbox Game DVR feature",
            "",
            IsRegistryKeyEnabled("System\\GameConfigStore", "GameDVR_Enabled", 0) &&
            IsRegistryKeyEnabledHKLM("SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR", "AllowGameDVR", 0)
        },
        {
            "Disable Auto Map Downloads",
            "Prevents Windows from automatically downloading map data",
            "",
            IsRegistryKeyEnabledHKLM("SOFTWARE\\Policies\\Microsoft\\Windows\\Maps", "AutoDownloadAndUpdateMapData", 0)
        },
        {
            "Disable Lock Screen Camera",
            "Disables the camera on the lock screen",
            "",
            IsRegistryKeyEnabledHKLM("SOFTWARE\\Policies\\Microsoft\\Windows\\Personalization", "NoLockScreenCamera", 1)
        },
        {
            "Disable Biometrics",
            "Disables Windows biometric features (including Windows Hello)",
            "",
            IsRegistryKeyEnabledHKLM("SOFTWARE\\Policies\\Microsoft\\Biometrics", "Enabled", 0) &&
            IsRegistryKeyEnabledHKLM("SOFTWARE\\Policies\\Microsoft\\Biometrics\\Credential Provider", "Enabled", 0)
        }
    };
    
    return tweaks;
}

// Registry ayarını doğrudan uygula - Windows API ile
inline void ApplyPrivacyTweak(PrivacyTweak& tweak) {
    const std::string cur_ver = "Software\\Microsoft\\Windows\\CurrentVersion\\";
    
    if (tweak.name == "Disable Sync Provider Notifications in File Explorer") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "Explorer\\Advanced").c_str(), 
            "ShowSyncProviderNotifications", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Fun Facts and Tips on Lock Screen") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "ContentDeliveryManager").c_str(), 
            "RotatingLockScreenOverlayEnabled", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "ContentDeliveryManager").c_str(), 
            "SubscribedContent-338387Enabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Suggested Content in Settings") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "ContentDeliveryManager").c_str(), 
            "SubscribedContent-338393Enabled", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "ContentDeliveryManager").c_str(), 
            "SubscribedContent-353694Enabled", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "ContentDeliveryManager").c_str(), 
            "SubscribedContent-353696Enabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Tips and Suggestions When Using Windows") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "ContentDeliveryManager").c_str(), 
            "SubscribedContent-338389Enabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable 'Get the Most out of Windows' Suggestions") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "UserProfileEngagement").c_str(), 
            "ScoobeSystemSettingEnabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Windows Welcome Experience") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "ContentDeliveryManager").c_str(), 
            "SubscribedContent-310093Enabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Personalized Ads") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "AdvertisingInfo").c_str(), 
            "Enabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Tailored Experiences") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "Privacy").c_str(), 
            "TailoredExperiencesWithDiagnosticDataEnabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Recommendations in Start Menu") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "Explorer\\Advanced").c_str(), 
            "Start_IrisRecommendations", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Notification Suggestions") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "Notifications\\Settings\\Windows.ActionCenter.SmartOptOut").c_str(), 
            "Enabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Bing Results in Windows Search") {
        const std::string cur_ver = "Software\\Microsoft\\Windows\\CurrentVersion\\";
        
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Policies\\Microsoft\\Windows\\Explorer", 
            "DisableSearchBoxSuggestions", tweak.enabled ? 1 : 0);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Policies\\Microsoft\\Windows", 
            "DisableSearchBoxSuggestions", tweak.enabled ? 1 : 0);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "Search").c_str(), 
            "BingSearchEnabled", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "Search").c_str(), 
            "CortanaConsent", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            std::string(cur_ver + "Search").c_str(), 
            "AllowSearchToUseLocation", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Edge Desktop Search Widget") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Policies\\Microsoft\\Edge", 
            "WebWidgetAllowed", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Location Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Camera Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\webcam", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Microphone Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\microphone", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Documents Library Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\documentsLibrary", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Pictures Library Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\picturesLibrary", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Videos Library Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\videosLibrary", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Broad File System Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\broadFileSystemAccess", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Account Information Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userAccountInformation", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Contacts Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\contacts", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Call History Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\phoneCallHistory", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Messaging Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\chat", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Notification Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userNotificationListener", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Email Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\email", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Tasks Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\userDataTasks", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Diagnostics Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\appDiagnostics", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Voice Activation") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Microsoft\\Speech_OneCore\\Settings\\VoiceActivation\\UserPreferenceForAllApps", 
            "AgentActivationEnabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Calendar Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\appointments", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Motion Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\activity", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Radio Access") {
        WindowsUtils::SetRegistryValueString(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\radios", 
            "Value", tweak.enabled ? "Deny" : "Allow");
    }
    else if (tweak.name == "Disable Activity Feed") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Policies\\Microsoft\\Windows\\System", 
            "EnableActivityFeed", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Notification Center") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Policies\\Microsoft\\Windows\\Explorer", 
            "DisableNotificationCenter", tweak.enabled ? 1 : 0);
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\PushNotifications", 
            "ToastEnabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Xbox Screen Recording") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "System\\GameConfigStore", 
            "GameDVR_Enabled", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR", 
            "AllowGameDVR", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Auto Map Downloads") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Policies\\Microsoft\\Windows\\Maps", 
            "AutoDownloadAndUpdateMapData", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Policies\\Microsoft\\Windows\\Maps", 
            "AllowUntriggeredNetworkTrafficOnSettingsPage", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Disable Lock Screen Camera") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Policies\\Microsoft\\Windows\\Personalization", 
            "NoLockScreenCamera", tweak.enabled ? 1 : 0);
    }
    else if (tweak.name == "Disable Biometrics") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Policies\\Microsoft\\Biometrics", 
            "Enabled", tweak.enabled ? 0 : 1);
        WindowsUtils::SetRegistryValueDWORD(HKEY_LOCAL_MACHINE, 
            "SOFTWARE\\Policies\\Microsoft\\Biometrics\\Credential Provider", 
            "Enabled", tweak.enabled ? 0 : 1);
    }
    else if (tweak.name == "Clear Recent Files on Exit") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 
            "ClearRecentDocsOnExit", tweak.enabled ? 1 : 0);
    }
    else if (tweak.name == "Disable Windows Copilot") {
        WindowsUtils::SetRegistryValueDWORD(HKEY_CURRENT_USER, 
            "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsCopilot", 
            "TurnOffWindowsCopilot", tweak.enabled ? 1 : 0);
    }
} 