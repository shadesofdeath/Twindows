#pragma once
#include <string>
#include <map>

// Function renamed to reflect that it now returns English translations
inline std::map<std::string, std::string> GetEnglishTranslations() {
    return {
        // Global
        {"Language", "Language"},
        {"English", "English"},
        {"Turkish", "Turkish"},
        {"German", "German"},
        {"French", "French"},
        {"Spanish", "Spanish"},
        {"Change Language", "Change Language"},
        {"Select Language", "Select Language"},

        // Tabs (Sekmeler)
        {"Privacy", "Privacy"},
        {"Performance", "Performance"},
        {"Appearance", "Appearance"},
        {"Security", "Security"},
        {"Settings", "Settings"},
        {"About", "About"},
        {"AppX Packages", "AppX Packages"},

        // Privacy Tab
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Privacy Settings"},
        {"Enable All", "Enable All"},
        {"Disable All", "Disable All"},

        // New Privacy Tweak Names and Tooltips
        {"Clear Recent Files on Exit", "Clear Recent Files on Exit"},
        {"Clears the list of recently opened files when you exit Windows", "Clears the list of recently opened files when you exit Windows"},

        {"Disable Windows Copilot", "Disable Windows Copilot"},
        {"Disables Windows Copilot AI assistant", "Disables Windows Copilot AI assistant"},

        // Privacy Tweak Names and Tooltips
        {"Disable Sync Provider Notifications in File Explorer", "Disable Sync Provider Notifications in File Explorer"},
        {"Disables file sync provider notifications in File Explorer", "Disables file sync provider notifications in File Explorer"},

        {"Disable Fun Facts and Tips on Lock Screen", "Disable Fun Facts and Tips on Lock Screen"},
        {"Disables fun facts, tips, tricks on your lock screen", "Disables fun facts, tips, tricks on your lock screen"},

        {"Disable Suggested Content in Settings", "Disable Suggested Content in Settings"},
        {"Disables suggested content in the Settings app", "Disables suggested content in the Settings app"},

        {"Disable Tips and Suggestions When Using Windows", "Disable Tips and Suggestions When Using Windows"},
        {"Disables tips and suggestions when using Windows", "Disables tips and suggestions when using Windows"},

        {"Disable 'Get the Most out of Windows' Suggestions", "Disable 'Get the Most out of Windows' Suggestions"},
        {"Disables suggestions on how to get the most out of Windows and finish setting up the device", "Disables suggestions on how to get the most out of Windows and finish setting up the device"},

        {"Disable Windows Welcome Experience", "Disable Windows Welcome Experience"},
        {"Disables the Windows welcome experience after updates and when signing in", "Disables the Windows welcome experience after updates and when signing in"},

        {"Disable Personalized Ads", "Disable Personalized Ads"},
        {"Prevents apps from showing personalized ads by using your advertising ID", "Prevents apps from showing personalized ads by using your advertising ID"},

        {"Disable Tailored Experiences", "Disable Tailored Experiences"},
        {"Disables tailored experiences with diagnostic data", "Disables tailored experiences with diagnostic data"},

        {"Disable Recommendations in Start Menu", "Disable Recommendations in Start Menu"},
        {"Disables recommendations for tips, shortcuts, new apps, and more in Start menu", "Disables recommendations for tips, shortcuts, new apps, and more in Start menu"},

        {"Disable Notification Suggestions", "Disable Notification Suggestions"},
        {"Disables notification suggestions about unused apps", "Disables notification suggestions about unused apps"},

        {"Disable Bing Results in Windows Search", "Disable Bing Results in Windows Search"},
        {"Disables Bing results in Windows Search", "Disables Bing results in Windows Search"},

        {"Disable Edge Desktop Search Widget", "Disable Edge Desktop Search Widget"},
        {"Disables the Edge search widget on desktop", "Disables the Edge search widget on desktop"},

        {"Disable Location Access", "Disable Location Access"},
        {"Prevents apps from accessing your location", "Prevents apps from accessing your location"},

        {"Disable Camera Access", "Disable Camera Access"},
        {"Prevents apps from accessing your camera", "Prevents apps from accessing your camera"},

        {"Disable Microphone Access", "Disable Microphone Access"},
        {"Prevents apps from accessing your microphone", "Prevents apps from accessing your microphone"},

        {"Disable Documents Library Access", "Disable Documents Library Access"},
        {"Prevents apps from accessing your documents library", "Prevents apps from accessing your documents library"},

        {"Disable Pictures Library Access", "Disable Pictures Library Access"},
        {"Prevents apps from accessing your pictures library", "Prevents apps from accessing your pictures library"},

        {"Disable Videos Library Access", "Disable Videos Library Access"},
        {"Prevents apps from accessing your videos library", "Prevents apps from accessing your videos library"},

        {"Disable Broad File System Access", "Disable Broad File System Access"},
        {"Prevents apps from accessing the file system broadly", "Prevents apps from accessing the file system broadly"},

        {"Disable Account Information Access", "Disable Account Information Access"},
        {"Prevents apps from accessing your name, picture, and account info", "Prevents apps from accessing your name, picture, and account info"},

        {"Disable Contacts Access", "Disable Contacts Access"},
        {"Prevents apps from accessing your contacts", "Prevents apps from accessing your contacts"},

        {"Disable Call History Access", "Disable Call History Access"},
        {"Prevents apps from accessing your call history", "Prevents apps from accessing your call history"},

        {"Disable Messaging Access", "Disable Messaging Access"},
        {"Prevents apps from accessing your messages", "Prevents apps from accessing your messages"},

        {"Disable Notification Access", "Disable Notification Access"},
        {"Prevents apps from accessing your notifications", "Prevents apps from accessing your notifications"},

        {"Disable Email Access", "Disable Email Access"},
        {"Prevents apps from accessing your email", "Prevents apps from accessing your email"},

        {"Disable Tasks Access", "Disable Tasks Access"},
        {"Prevents apps from accessing your user data tasks", "Prevents apps from accessing your user data tasks"},

        {"Disable Diagnostics Access", "Disable Diagnostics Access"},
        {"Prevents apps from accessing your diagnostic information", "Prevents apps from accessing your diagnostic information"},

        {"Disable Voice Activation", "Disable Voice Activation"},
        {"Disables voice activation for all apps", "Disables voice activation for all apps"},

        {"Disable Calendar Access", "Disable Calendar Access"},
        {"Prevents apps from accessing your calendar appointments", "Prevents apps from accessing your calendar appointments"},

        {"Disable Motion Access", "Disable Motion Access"},
        {"Prevents apps from accessing motion data", "Prevents apps from accessing motion data"},

        {"Disable Radio Access", "Disable Radio Access"},
        {"Prevents apps from accessing radio controls", "Prevents apps from accessing radio controls"},

        {"Disable Activity Feed", "Disable Activity Feed"},
        {"Disables the Windows activity feed", "Disables the Windows activity feed"},

        {"Disable Notification Center", "Disable Notification Center"},
        {"Disables the Windows notification center", "Disables the Windows notification center"},

        {"Disable Xbox Screen Recording", "Disable Xbox Screen Recording"},
        {"Disables the Xbox Game DVR feature", "Disables the Xbox Game DVR feature"},

        {"Disable Auto Map Downloads", "Disable Auto Map Downloads"},
        {"Prevents Windows from automatically downloading map data", "Prevents Windows from automatically downloading map data"},

        {"Disable Lock Screen Camera", "Disable Lock Screen Camera"},
        {"Disables the camera on the lock screen", "Disables the camera on the lock screen"},

        {"Disable Biometrics", "Disable Biometrics"},
        {"Disables Windows biometric features (including Windows Hello)", "Disables Windows biometric features (including Windows Hello)"},

        // Performance Tab
        {"Windows Tweaker - Performance Settings", "Windows Tweaker - Performance Settings"},

        // New Performance Tweak Names and Tooltips
        {"Enable Confirm File Delete Dialog", "Enable Confirm File Delete Dialog"},
        {"Shows a confirmation dialog when deleting files", "Shows a confirmation dialog when deleting files"},

        {"Permanently Delete Files (Skip Recycle Bin)", "Permanently Delete Files (Skip Recycle Bin)"},
        {"Deletes files permanently without moving them to the Recycle Bin", "Deletes files permanently without moving them to the Recycle Bin"},

        // Performance Tweak Names and Tooltips
        {"Disable Fullscreen Optimizations", "Disable Fullscreen Optimizations"},
        {"Disables Windows fullscreen optimizations for better game performance", "Disables Windows fullscreen optimizations for better game performance"},

        {"Disable Mouse Acceleration", "Disable Mouse Acceleration"},
        {"Removes mouse acceleration for more consistent cursor movement", "Removes mouse acceleration for more consistent cursor movement"},

        {"Disable Game Bar", "Disable Game Bar"},
        {"Disables Game Bar and related features to reduce overhead", "Disables Game Bar and related features to reduce overhead"},

        {"Disable Game Mode", "Disable Game Mode"},
        {"Turns off Windows Game Mode which can cause issues with some games", "Turns off Windows Game Mode which can cause issues with some games"},

        {"Activate Ultimate Performance Mode", "Activate Ultimate Performance Mode"},
        {"Activates the hidden Ultimate Performance power plan for maximum performance", "Activates the hidden Ultimate Performance power plan for maximum performance"},

        {"Disable Hardware Accelerated GPU Scheduling", "Disable Hardware Accelerated GPU Scheduling"},
        {"Disables HAGS which can cause issues with some systems", "Disables HAGS which can cause issues with some systems"},

        {"Limit Windows Defender Usage", "Limit Windows Defender Usage"},
        {"Limits Windows Defender CPU usage for better performance", "Limits Windows Defender CPU usage for better performance"},

        {"Disable Core Isolation", "Disable Core Isolation"},
        {"Disables memory integrity for better performance (reduces security)", "Disables memory integrity for better performance (reduces security)"},

        {"Disable Prefetch", "Disable Prefetch"},
        {"Disables Windows Prefetch service to free up resources", "Disables Windows Prefetch service to free up resources"},

        {"Disable Storage Sense", "Disable Storage Sense"},
        {"Disables automatic disk cleanup to prevent background disk activity", "Disables automatic disk cleanup to prevent background disk activity"},

        {"Disable Windows Search", "Disable Windows Search"},
        {"Disables Windows Search indexing service to free up system resources", "Disables Windows Search indexing service to free up system resources"},

        {"Disable Hibernation", "Disable Hibernation"},
        {"Disables system hibernation to free up disk space and resources", "Disables system hibernation to free up disk space and resources"},

        // Appearance Tab
        {"Windows Tweaker - Appearance Settings", "Windows Tweaker - Appearance Settings"},
        {"Appearance Changes Notice", "Explorer must be restarted for changes"}, // Adjusted slightly for better English flow
        {"No appearance changes requiring restart", "No appearance changes requiring restart"},
        {"Restart Explorer", "Restart Explorer"},

        // New Appearance Tweak Names and Tooltips
        {"Hide Personalized Web Recommendations", "Hide Personalized Web Recommendations"},
        {"Removes personalized website recommendations from the Start menu", "Removes personalized website recommendations from the Start menu"},

        {"Hide Recommended Section in Start Menu", "Hide Recommended Section in Start Menu"},
        {"Completely removes the Recommended section from the Start menu", "Completely removes the Recommended section from the Start menu"},

        {"Hide Clock in System Tray", "Hide Clock in System Tray"},
        {"Hides the system clock from the taskbar notification area", "Hides the system clock from the taskbar notification area"},

        {"Hide Meet Now Icon", "Hide Meet Now Icon"},
        {"Removes the Meet Now (instant meeting) icon from the taskbar", "Removes the Meet Now (instant meeting) icon from the taskbar"},

        {"Disable All Balloon Notifications", "Disable All Balloon Notifications"},
        {"Turns off all balloon notifications from the system tray", "Turns off all balloon notifications from the system tray"},

        {"Hide Details Pane in File Explorer", "Hide Details Pane in File Explorer"},
        {"Hides the details pane in File Explorer that shows file properties", "Hides the details pane in File Explorer that shows file properties"},

        // Appearance Tweak Names and Tooltips
        {"Disable Bing Search in Start Menu", "Disable Bing Search in Start Menu"},
        {"Controls whether the search box in the Windows Start menu performs Bing web searches", "Controls whether the search box in the Windows Start menu performs Bing web searches"},

        {"Center Taskbar Icons", "Center Taskbar Icons"},
        {"Controls whether taskbar icons are displayed centered or left-aligned", "Controls whether taskbar icons are displayed centered or left-aligned"},

        {"Enable Dark Mode", "Enable Dark Mode"},
        {"Controls whether Windows uses dark theme. Applies to apps and system interface", "Controls whether Windows uses dark theme. Applies to apps and system interface"},

        {"Show Detailed BSoD", "Show Detailed BSoD"}, // BSoD = Blue Screen of Death
        {"Controls whether detailed technical information is displayed on blue screen errors", "Controls whether detailed technical information is displayed on blue screen errors"},

        {"Enable Mouse Acceleration", "Enable Mouse Acceleration"},
        {"When enabled, cursor movement is affected by the speed of your physical mouse movements", "When enabled, cursor movement is affected by the speed of your physical mouse movements"},

        {"Enable NumLock on Startup", "Enable NumLock on Startup"},
        {"Controls the state of the NumLock key when your computer starts", "Controls the state of the NumLock key when your computer starts"},

        {"Show Search Button in Taskbar", "Show Search Button in Taskbar"},
        {"When enabled, the search button is displayed in the taskbar", "When enabled, the search button is displayed in the taskbar"},

        {"Show File Extensions", "Show File Extensions"},
        {"When enabled, file extensions (.txt, .jpg, etc.) are made visible", "When enabled, file extensions (.txt, .jpg, etc.) are made visible"},

        {"Show Hidden Files", "Show Hidden Files"},
        {"When enabled, hidden files are displayed", "When enabled, hidden files are displayed"},

        {"Enable Snap Assist Flyout", "Enable Snap Assist Flyout"},
        {"When enabled, helper flyout is displayed when hovering screen corners or during window snapping", "When enabled, helper flyout is displayed when hovering screen corners or during window snapping"},

        {"Enable Snap Assist Suggestion", "Enable Snap Assist Suggestion"},
        {"When enabled, suggestions for other apps to fill remaining areas are shown during window snapping", "When enabled, suggestions for other apps to fill remaining areas are shown during window snapping"},

        {"Enable Snap Window", "Enable Snap Window"},
        {"When enabled, you can snap windows by dragging them to the edges of the screen", "When enabled, you can snap windows by dragging them to the edges of the screen"},

        {"Enable Sticky Keys", "Enable Sticky Keys"},
        {"When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries", "When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries"},

        {"Show Task View Button in Taskbar", "Show Task View Button in Taskbar"},
        {"When enabled, the Task View button is displayed in the taskbar", "When enabled, the Task View button is displayed in the taskbar"},

        {"Show Verbose Messages During Logon", "Show Verbose Messages During Logon"},
        {"Shows detailed messages during login process for troubleshooting and diagnostics", "Shows detailed messages during login process for troubleshooting and diagnostics"},

        {"Show Widgets Button in Taskbar", "Show Widgets Button in Taskbar"},
        {"When enabled, the Widgets button is displayed in the taskbar", "When enabled, the Widgets button is displayed in the taskbar"},

        {"Enable Classic Right-Click Menu", "Enable Classic Right-Click Menu"},
        {"Shows old (compact) context menu when right-clicking in file explorer on Windows 11", "Shows old (compact) context menu when right-clicking in file explorer on Windows 11"},

        {"Remove Gallery from Navigation Pane", "Remove Gallery from Navigation Pane"},
        {"Removes or adds the Gallery item from the navigation pane on the left side of File Explorer", "Removes or adds the Gallery item from the navigation pane on the left side of File Explorer"},

        {"Restarts Windows Explorer to apply changes", "Restarts Windows Explorer to apply changes"},

        // Security Tab
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Security Settings"},

        // Security Tweak Names and Tooltips (Note: Original keys were Turkish here, kept them as requested)
        {"Windows Defender'ı Etkinleştir", "Enable Windows Defender"},
        {"Windows Defender antivirüs servisi", "Windows Defender antivirus service"},

        {"Gerçek Zamanlı Korumayı Etkinleştir", "Enable Real-time Protection"},
        {"Windows Defender'ın gerçek zamanlı koruma özelliği", "Windows Defender's real-time protection feature"},

        {"SmartScreen'i Etkinleştir", "Enable SmartScreen"},
        {"Microsoft SmartScreen filtreleme özelliği", "Microsoft SmartScreen filtering feature"},

        {"Windows Güvenlik Duvarını Etkinleştir", "Enable Windows Firewall"},
        {"Windows Güvenlik Duvarı servisi", "Windows Firewall service"},

        {"UAC'yi Etkinleştir", "Enable UAC"},
        {"Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar", "User Account Control (UAC) - requires user confirmation for actions requiring administrator privileges"},

        {"UAC Seviyesini Yükselt", "Elevate UAC Level"},
        {"UAC seviyesini yüksek ayara getirir", "Sets the UAC level to high setting"},

        {"Güvenli Masaüstünde UAC'yi Etkinleştir", "Enable UAC on Secure Desktop"},
        {"UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir", "Shows UAC dialogs on a secure desktop inaccessible to malware"},

        {"Son Kullanıcı Adını Gizle", "Hide Last Username"},
        {"Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez", "Does not show the name of the last logged-in user on the Windows sign-in screen"},

        {"SMB1 Protokolünü Devre Dışı Bırak", "Disable SMB1 Protocol"},
        {"Güvenlik açığı bulunan eski SMB1 protokolünü kapatır", "Turns off the vulnerable legacy SMB1 protocol"},

        {"LLMNR Protokolünü Devre Dışı Bırak", "Disable LLMNR Protocol"},
        {"Link-Local Multicast Name Resolution protokolünü devre dışı bırakır", "Disables the Link-Local Multicast Name Resolution protocol"},

        {"NBT-NS'yi Devre Dışı Bırak", "Disable NBT-NS"},
        {"NetBIOS Name Service protokolünü devre dışı bırakır", "Disables the NetBIOS Name Service protocol"},

        {"Uzak Masaüstü Güvenlik Seviyesini Yükselt", "Elevate Remote Desktop Security Level"},
        {"Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar", "Sets the Remote Desktop Protocol (RDP) security level to high"},

        {"RDP için NLA Kimlik Doğrulamasını Etkinleştir", "Enable NLA Authentication for RDP"},
        {"RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir", "Requires Network Level Authentication (NLA) for RDP"},

        {"RDP Şifreleme Seviyesini Yükselt", "Elevate RDP Encryption Level"},
        {"RDP için şifreleme seviyesini yüksek olarak ayarlar", "Sets the encryption level for RDP to high"},

        {"AutoRun'u Devre Dışı Bırak", "Disable AutoRun"},
        {"Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır", "Disables the AutoRun feature on removable media"},

        {"USB Depolamayı Etkinleştir", "Enable USB Storage"},
        {"USB depolama cihazlarını etkinleştirir veya devre dışı bırakır", "Enables or disables USB storage devices"},

        {"PowerShell Yürütme İlkesini Güvenli Yap", "Secure PowerShell Execution Policy"},
        {"PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar", "Sets the execution policy for PowerShell scripts to RemoteSigned"},

        {"PowerShell Komut Kaydetmeyi Etkinleştir", "Enable PowerShell Command Logging"},
        {"PowerShell komut blokları için günlük kaydını etkinleştirir", "Enables logging for PowerShell command blocks"},

        {"Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir", "Enable Script Host Security"},
        {"Windows Script Host güvenliğini etkinleştirir", "Enables Windows Script Host security"},

        {"Windows Update'i Etkinleştir", "Enable Windows Update"},
        {"Windows Update servisini etkinleştirir", "Enables the Windows Update service"},

        {"Otomatik Güncellemeleri Etkinleştir", "Enable Automatic Updates"},
        {"Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar", "Allows Windows to automatically download and install updates"},

        {"WPAD Protokolünü Devre Dışı Bırak", "Disable WPAD Protocol"},
        {"Web Proxy Auto-Discovery protokolünü devre dışı bırakır", "Disables the Web Proxy Auto-Discovery protocol"},

        {"WinRM Şifresiz Trafiği Devre Dışı Bırak", "Disable WinRM Unencrypted Traffic"},
        {"Windows Remote Management için şifresiz trafiği engeller", "Blocks unencrypted traffic for Windows Remote Management"},

        // AppX Packages Tab
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - AppX Packages"},
        {"Remove Selected Apps", "Remove Selected Apps"},
        {"Select All", "Select All"},
        {"Deselect All", "Deselect All"},
        {"Search apps", "Search apps"},
        {"Removing apps...", "Removing apps..."},
        {"Successfully removed", "Successfully removed"},
        {"application(s)", "application(s)"},
        {"No apps selected", "No apps selected"},
        {"System Apps", "System Apps"},
        {"Warning: System apps are essential for Windows", "Warning: System apps are essential for Windows"},
        {"Removing", "Removing"},

        // Settings Tab
        {"Windows Tweaker - Settings", "Windows Tweaker - Settings"},

        // About Tab
        {"Windows Tweaker - About", "Windows Tweaker - About"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "A comprehensive Windows 11 optimization and tweaking tool"},
        {"Developer", "Developer"},
        {"Version", "Version"},
        {"License", "License"},

        // Dialog (No specific items listed, assumed placeholders if needed)

        // Toggle
        {"ToggleOn", "On"}, // Changed from "Açık"
        {"ToggleOff", "Off"} // Changed from "Kapalı"
    };
}