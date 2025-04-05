#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <atlbase.h> // CComPtr için
#include <shobjidl.h> // CLSID_AppxFactory için
#include <appxpackaging.h> // IAppxFactory, IAppxPackageReader vb.
#include "windows_utils.h" // Ortak Windows API işlevleri için

// AppX paketi yapısı
struct AppXPackage {
    std::string packageName;
    std::string displayName;
    std::string publisher;
    std::string version;
    bool isSelected;
};

// Yüklü AppX paketlerini listele
inline std::vector<AppXPackage> GetInstalledAppXPackages() {
    std::vector<AppXPackage> packages;
    
    // Önceden tanımlanmış Win11Debloat listesi
    std::vector<std::string> packagesList = {
        "Clipchamp.Clipchamp",
        "Microsoft.3DBuilder",
        "Microsoft.549981C3F5F10", // Cortana app
        "Microsoft.BingFinance",
        "Microsoft.BingFoodAndDrink",
        "Microsoft.BingHealthAndFitness",
        "Microsoft.BingNews",
        "Microsoft.BingSports",
        "Microsoft.BingTranslator",
        "Microsoft.BingTravel",
        "Microsoft.BingWeather",
        "Microsoft.Getstarted",
        "Microsoft.Messaging",
        "Microsoft.Microsoft3DViewer",
        "Microsoft.MicrosoftJournal",
        "Microsoft.MicrosoftOfficeHub",
        "Microsoft.MicrosoftPowerBIForWindows",
        "Microsoft.MicrosoftSolitaireCollection",
        "Microsoft.MicrosoftStickyNotes",
        "Microsoft.MixedReality.Portal",
        "Microsoft.NetworkSpeedTest",
        "Microsoft.News",
        "Microsoft.Office.OneNote",
        "Microsoft.Office.Sway",
        "Microsoft.OneConnect",
        "Microsoft.Print3D",
        "Microsoft.SkypeApp",
        "Microsoft.Todos",
        "Microsoft.WindowsAlarms",
        "Microsoft.WindowsFeedbackHub",
        "Microsoft.WindowsMaps",
        "Microsoft.WindowsSoundRecorder",
        "Microsoft.XboxApp", // Old Xbox Console Companion App
        "Microsoft.ZuneVideo",
        "MicrosoftCorporationII.MicrosoftFamily", // Family Safety App
        "MicrosoftCorporationII.QuickAssist",
        "MicrosoftTeams", // Old MS Teams personal (MS Store)
        "MSTeams", // New MS Teams app
        "ACGMediaPlayer",
        "ActiproSoftwareLLC",
        "AdobeSystemsIncorporated.AdobePhotoshopExpress",
        "Amazon.com.Amazon",
        "AmazonVideo.PrimeVideo",
        "Asphalt8Airborne",
        "AutodeskSketchBook",
        "CaesarsSlotsFreeCasino",
        "COOKINGFEVER",
        "CyberLinkMediaSuiteEssentials",
        "DisneyMagicKingdoms",
        "Disney",
        "DrawboardPDF",
        "Duolingo-LearnLanguagesforFree",
        "EclipseManager",
        "Facebook",
        "FarmVille2CountryEscape",
        "fitbit",
        "Flipboard",
        "HiddenCity",
        "HULULLC.HULUPLUS",
        "iHeartRadio",
        "Instagram",
        "king.com.BubbleWitch3Saga",
        "king.com.CandyCrushSaga",
        "king.com.CandyCrushSodaSaga",
        "LinkedInforWindows",
        "MarchofEmpires",
        "Netflix",
        "NYTCrossword",
        "OneCalendar",
        "PandoraMediaInc",
        "PhototasticCollage",
        "PicsArt-PhotoStudio",
        "Plex",
        "PolarrPhotoEditorAcademicEdition",
        "Royal Revolt",
        "Shazam",
        "Sidia.LiveWallpaper",
        "SlingTV",
        "Spotify",
        "TikTok",
        "TuneInRadio",
        "Twitter",
        "Viber",
        "WinZipUniversal",
        "Wunderlist",
        "XING"
    };
    
    // Temel sistemde kalması gereken uygulamalar
    std::vector<std::string> systemApps = {
        "Microsoft.BingSearch",
        "Microsoft.Copilot",
        "Microsoft.Edge",
        "Microsoft.GetHelp",
        "Microsoft.MSPaint",
        "Microsoft.OneDrive",
        "Microsoft.Paint",
        "Microsoft.ScreenSketch",
        "Microsoft.Whiteboard",
        "Microsoft.Windows.Photos",
        "Microsoft.WindowsCalculator",
        "Microsoft.WindowsCamera",
        "Microsoft.WindowsNotepad",
        "Microsoft.WindowsStore",
        "Microsoft.WindowsTerminal",
        "Microsoft.Xbox.TCUI",
        "Microsoft.XboxIdentityProvider",
        "Microsoft.XboxSpeechToTextOverlay",
        "Microsoft.YourPhone",
        "Microsoft.ZuneMusic",
        "MicrosoftWindows.CrossDevice",
        "Microsoft.GamingApp",
        "Microsoft.OutlookForWindows",
        "Microsoft.People",
        "Microsoft.PowerAutomateDesktop",
        "Microsoft.RemoteDesktop",
        "Microsoft.Windows.DevHome",
        "Microsoft.windowscommunicationsapps",
        "Microsoft.XboxGameOverlay",
        "Microsoft.XboxGamingOverlay"
    };
    
    // Kaldırılabilir AppX paketlerini ekle
    for (const auto& packageName : packagesList) {
        AppXPackage package;
        package.packageName = packageName;
        
        // Görünen ad için uygun formatlama
        std::string displayName = packageName;
        size_t lastDot = displayName.find_last_of('.');
        if (lastDot != std::string::npos) {
            displayName = displayName.substr(lastDot + 1);
        }
        
        package.displayName = displayName;
        package.publisher = "Microsoft or third party";
        package.version = "Unknown";
        package.isSelected = false; // Varsayılan olarak seçili değil
        
        packages.push_back(package);
    }
    
    // Korunacak uygulamaları ekle - seçim devre dışı bırakılmış olarak
    for (const auto& packageName : systemApps) {
        AppXPackage package;
        package.packageName = packageName;
        
        // Görünen ad için uygun formatlama
        std::string displayName = packageName;
        size_t lastDot = displayName.find_last_of('.');
        if (lastDot != std::string::npos) {
            displayName = displayName.substr(lastDot + 1);
        }
        
        package.displayName = displayName + " (System)";
        package.publisher = "Microsoft";
        package.version = "Unknown";
        package.isSelected = false; // Varsayılan olarak seçili değil
        
        packages.push_back(package);
    }
    
    return packages;
}

// AppX paketini kaldır
inline bool RemoveAppXPackage(const std::string& packageName) {
    // PowerShell komutu oluştur
    std::string command = "powershell -Command \"Get-AppxPackage *" + packageName + "* | Remove-AppxPackage\"";
    
    // Komutu çalıştır
    return WindowsUtils::ExecuteCommand(command.c_str());
}

// Seçili AppX paketlerini kaldır
inline int RemoveSelectedAppXPackages(std::vector<AppXPackage>& packages) {
    int removedCount = 0;
    
    for (auto& package : packages) {
        if (package.isSelected) {
            if (RemoveAppXPackage(package.packageName)) {
                removedCount++;
                package.isSelected = false; // Seçimi temizle
            }
        }
    }
    
    return removedCount;
} 