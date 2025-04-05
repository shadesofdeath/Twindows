#pragma once
#include <string>
#include <map>

// Funktion umbenannt, um widerzuspiegeln, dass sie jetzt deutsche Übersetzungen zurückgibt
inline std::map<std::string, std::string> GetGermanTranslations() {
    return {
        // Global
        {"Language", "Sprache"},
        {"English", "Englisch"},
        {"Turkish", "Türkisch"},
        {"German", "Deutsch"},
        {"French", "Französisch"},
        {"Spanish", "Spanisch"},
        {"Change Language", "Sprache ändern"},
        {"Select Language", "Sprache auswählen"},

        // Tabs (Registerkarten)
        {"Privacy", "Datenschutz"},
        {"Performance", "Leistung"},
        {"Appearance", "Darstellung"},
        {"Security", "Sicherheit"},
        {"Settings", "Einstellungen"},
        {"About", "Info"},
        {"AppX Packages", "AppX-Pakete"},

        // Datenschutz-Tab
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Datenschutzeinstellungen"},
        {"Enable All", "Alle aktivieren"},
        {"Disable All", "Alle deaktivieren"},

        // Neue Datenschutz-Optimierungsnamen und Tooltips
        {"Clear Recent Files on Exit", "Zuletzt verwendete Dateien beim Beenden löschen"},
        {"Clears the list of recently opened files when you exit Windows", "Löscht die Liste der zuletzt geöffneten Dateien, wenn Sie Windows beenden"},

        {"Disable Windows Copilot", "Windows Copilot deaktivieren"},
        {"Disables Windows Copilot AI assistant", "Deaktiviert den Windows Copilot KI-Assistenten"},

        // Datenschutz-Optimierungsnamen und Tooltips
        {"Disable Sync Provider Notifications in File Explorer", "Benachrichtigungen von Synchronisierungsanbietern im Datei-Explorer deaktivieren"},
        {"Disables file sync provider notifications in File Explorer", "Deaktiviert Benachrichtigungen von Dateisynchronisierungsanbietern im Datei-Explorer"},

        {"Disable Fun Facts and Tips on Lock Screen", "Unterhaltsame Fakten und Tipps auf dem Sperrbildschirm deaktivieren"},
        {"Disables fun facts, tips, tricks on your lock screen", "Deaktiviert unterhaltsame Fakten, Tipps und Tricks auf Ihrem Sperrbildschirm"},

        {"Disable Suggested Content in Settings", "Vorgeschlagene Inhalte in den Einstellungen deaktivieren"},
        {"Disables suggested content in the Settings app", "Deaktiviert vorgeschlagene Inhalte in der Einstellungs-App"},

        {"Disable Tips and Suggestions When Using Windows", "Tipps und Vorschläge bei der Verwendung von Windows deaktivieren"},
        {"Disables tips and suggestions when using Windows", "Deaktiviert Tipps und Vorschläge bei der Verwendung von Windows"},

        {"Disable 'Get the Most out of Windows' Suggestions", "Vorschläge 'Optimal Nutzen von Windows' deaktivieren"},
        {"Disables suggestions on how to get the most out of Windows and finish setting up the device", "Deaktiviert Vorschläge, wie Sie Windows optimal nutzen und die Geräteeinrichtung abschließen können"},

        {"Disable Windows Welcome Experience", "Windows-Willkommensseite deaktivieren"},
        {"Disables the Windows welcome experience after updates and when signing in", "Deaktiviert die Windows-Willkommensseite nach Updates und bei der Anmeldung"},

        {"Disable Personalized Ads", "Personalisierte Werbung deaktivieren"},
        {"Prevents apps from showing personalized ads by using your advertising ID", "Verhindert, dass Apps personalisierte Werbung mithilfe Ihrer Werbe-ID anzeigen"},

        {"Disable Tailored Experiences", "Angepasste Erfahrungen deaktivieren"},
        {"Disables tailored experiences with diagnostic data", "Deaktiviert angepasste Erfahrungen mit Diagnosedaten"},

        {"Disable Recommendations in Start Menu", "Empfehlungen im Startmenü deaktivieren"},
        {"Disables recommendations for tips, shortcuts, new apps, and more in Start menu", "Deaktiviert Empfehlungen für Tipps, Verknüpfungen, neue Apps und mehr im Startmenü"},

        {"Disable Notification Suggestions", "Benachrichtigungsvorschläge deaktivieren"},
        {"Disables notification suggestions about unused apps", "Deaktiviert Benachrichtigungsvorschläge zu nicht verwendeten Apps"},

        {"Disable Bing Results in Windows Search", "Bing-Ergebnisse in der Windows-Suche deaktivieren"},
        {"Disables Bing results in Windows Search", "Deaktiviert Bing-Ergebnisse in der Windows-Suche"},

        {"Disable Edge Desktop Search Widget", "Edge Desktop-Such-Widget deaktivieren"},
        {"Disables the Edge search widget on desktop", "Deaktiviert das Edge-Such-Widget auf dem Desktop"},

        {"Disable Location Access", "Standortzugriff deaktivieren"},
        {"Prevents apps from accessing your location", "Verhindert, dass Apps auf Ihren Standort zugreifen"},

        {"Disable Camera Access", "Kamerazugriff deaktivieren"},
        {"Prevents apps from accessing your camera", "Verhindert, dass Apps auf Ihre Kamera zugreifen"},

        {"Disable Microphone Access", "Mikrofonzugriff deaktivieren"},
        {"Prevents apps from accessing your microphone", "Verhindert, dass Apps auf Ihr Mikrofon zugreifen"},

        {"Disable Documents Library Access", "Zugriff auf Dokumentenbibliothek deaktivieren"},
        {"Prevents apps from accessing your documents library", "Verhindert, dass Apps auf Ihre Dokumentenbibliothek zugreifen"},

        {"Disable Pictures Library Access", "Zugriff auf Bilderbibliothek deaktivieren"},
        {"Prevents apps from accessing your pictures library", "Verhindert, dass Apps auf Ihre Bilderbibliothek zugreifen"},

        {"Disable Videos Library Access", "Zugriff auf Videobibliothek deaktivieren"},
        {"Prevents apps from accessing your videos library", "Verhindert, dass Apps auf Ihre Videobibliothek zugreifen"},

        {"Disable Broad File System Access", "Breiten Dateisystemzugriff deaktivieren"},
        {"Prevents apps from accessing the file system broadly", "Verhindert, dass Apps breit auf das Dateisystem zugreifen"},

        {"Disable Account Information Access", "Zugriff auf Kontoinformationen deaktivieren"},
        {"Prevents apps from accessing your name, picture, and account info", "Verhindert, dass Apps auf Ihren Namen, Ihr Bild und Ihre Kontoinformationen zugreifen"},

        {"Disable Contacts Access", "Kontaktzugriff deaktivieren"},
        {"Prevents apps from accessing your contacts", "Verhindert, dass Apps auf Ihre Kontakte zugreifen"},

        {"Disable Call History Access", "Zugriff auf Anrufverlauf deaktivieren"},
        {"Prevents apps from accessing your call history", "Verhindert, dass Apps auf Ihren Anrufverlauf zugreifen"},

        {"Disable Messaging Access", "Nachrichtenzugriff deaktivieren"},
        {"Prevents apps from accessing your messages", "Verhindert, dass Apps auf Ihre Nachrichten zugreifen"},

        {"Disable Notification Access", "Benachrichtigungszugriff deaktivieren"},
        {"Prevents apps from accessing your notifications", "Verhindert, dass Apps auf Ihre Benachrichtigungen zugreifen"},

        {"Disable Email Access", "E-Mail-Zugriff deaktivieren"},
        {"Prevents apps from accessing your email", "Verhindert, dass Apps auf Ihre E-Mails zugreifen"},

        {"Disable Tasks Access", "Aufgabenzugriff deaktivieren"},
        {"Prevents apps from accessing your user data tasks", "Verhindert, dass Apps auf Ihre Benutzerdatenaufgaben zugreifen"},

        {"Disable Diagnostics Access", "Diagnosezugriff deaktivieren"},
        {"Prevents apps from accessing your diagnostic information", "Verhindert, dass Apps auf Ihre Diagnoseinformationen zugreifen"},

        {"Disable Voice Activation", "Sprachaktivierung deaktivieren"},
        {"Disables voice activation for all apps", "Deaktiviert die Sprachaktivierung für alle Apps"},

        {"Disable Calendar Access", "Kalenderzugriff deaktivieren"},
        {"Prevents apps from accessing your calendar appointments", "Verhindert, dass Apps auf Ihre Kalendertermine zugreifen"},

        {"Disable Motion Access", "Bewegungsdatenzugriff deaktivieren"},
        {"Prevents apps from accessing motion data", "Verhindert, dass Apps auf Bewegungsdaten zugreifen"},

        {"Disable Radio Access", "Funkzugriff deaktivieren"},
        {"Prevents apps from accessing radio controls", "Verhindert, dass Apps auf Funksteuerungen zugreifen"},

        {"Disable Activity Feed", "Aktivitätsfeed deaktivieren"},
        {"Disables the Windows activity feed", "Deaktiviert den Windows-Aktivitätsfeed"},

        {"Disable Notification Center", "Info-Center deaktivieren"},
        {"Disables the Windows notification center", "Deaktiviert das Windows-Info-Center"},

        {"Disable Xbox Screen Recording", "Xbox-Bildschirmaufnahme deaktivieren"},
        {"Disables the Xbox Game DVR feature", "Deaktiviert die Xbox Game DVR-Funktion"},

        {"Disable Auto Map Downloads", "Automatische Kartendownloads deaktivieren"},
        {"Prevents Windows from automatically downloading map data", "Verhindert, dass Windows automatisch Kartendaten herunterlädt"},

        {"Disable Lock Screen Camera", "Sperrbildschirmkamera deaktivieren"},
        {"Disables the camera on the lock screen", "Deaktiviert die Kamera auf dem Sperrbildschirm"},

        {"Disable Biometrics", "Biometrie deaktivieren"},
        {"Disables Windows biometric features (including Windows Hello)", "Deaktiviert biometrische Funktionen von Windows (einschließlich Windows Hello)"},

        // Leistungs-Tab
        {"Windows Tweaker - Performance Settings", "Windows Tweaker - Leistungseinstellungen"},

        // Neue Leistungs-Optimierungsnamen und Tooltips
        {"Enable Confirm File Delete Dialog", "Bestätigungsdialog beim Löschen von Dateien aktivieren"},
        {"Shows a confirmation dialog when deleting files", "Zeigt einen Bestätigungsdialog beim Löschen von Dateien an"},

        {"Permanently Delete Files (Skip Recycle Bin)", "Dateien dauerhaft löschen (Papierkorb überspringen)"},
        {"Deletes files permanently without moving them to the Recycle Bin", "Löscht Dateien dauerhaft, ohne sie in den Papierkorb zu verschieben"},

        // Leistungs-Optimierungsnamen und Tooltips
        {"Disable Fullscreen Optimizations", "Vollbildoptimierungen deaktivieren"},
        {"Disables Windows fullscreen optimizations for better game performance", "Deaktiviert Windows-Vollbildoptimierungen für bessere Spieleleistung"},

        {"Disable Mouse Acceleration", "Mausbeschleunigung deaktivieren"},
        {"Removes mouse acceleration for more consistent cursor movement", "Entfernt die Mausbeschleunigung für eine konsistentere Cursorbewegung"},

        {"Disable Game Bar", "Spieleleiste deaktivieren"},
        {"Disables Game Bar and related features to reduce overhead", "Deaktiviert die Spieleleiste und zugehörige Funktionen, um den Overhead zu reduzieren"},

        {"Disable Game Mode", "Spielmodus deaktivieren"},
        {"Turns off Windows Game Mode which can cause issues with some games", "Schaltet den Windows-Spielmodus aus, der bei einigen Spielen Probleme verursachen kann"},

        {"Activate Ultimate Performance Mode", "Modus 'Ultimative Leistung' aktivieren"},
        {"Activates the hidden Ultimate Performance power plan for maximum performance", "Aktiviert den versteckten Energiesparplan 'Ultimative Leistung' für maximale Leistung"},

        {"Disable Hardware Accelerated GPU Scheduling", "Hardwarebeschleunigte GPU-Planung deaktivieren"},
        {"Disables HAGS which can cause issues with some systems", "Deaktiviert HAGS, was bei einigen Systemen Probleme verursachen kann"},

        {"Limit Windows Defender Usage", "Windows Defender-Nutzung begrenzen"},
        {"Limits Windows Defender CPU usage for better performance", "Begrenzt die CPU-Nutzung von Windows Defender für bessere Leistung"},

        {"Disable Core Isolation", "Kernisolierung deaktivieren"},
        {"Disables memory integrity for better performance (reduces security)", "Deaktiviert die Speicherintegrität für bessere Leistung (reduziert die Sicherheit)"},

        {"Disable Prefetch", "Prefetch deaktivieren"},
        {"Disables Windows Prefetch service to free up resources", "Deaktiviert den Windows Prefetch-Dienst, um Ressourcen freizugeben"},

        {"Disable Storage Sense", "Speicheroptimierung deaktivieren"},
        {"Disables automatic disk cleanup to prevent background disk activity", "Deaktiviert die automatische Datenträgerbereinigung, um Hintergrund-Datenträgeraktivitäten zu verhindern"},

        {"Disable Windows Search", "Windows-Suche deaktivieren"},
        {"Disables Windows Search indexing service to free up system resources", "Deaktiviert den Windows-Suchindizierungsdienst, um Systemressourcen freizugeben"},

        {"Disable Hibernation", "Ruhezustand deaktivieren"},
        {"Disables system hibernation to free up disk space and resources", "Deaktiviert den Systemruhezustand, um Speicherplatz und Ressourcen freizugeben"},

        // Darstellungs-Tab
        {"Windows Tweaker - Appearance Settings", "Windows Tweaker - Darstellungseinstellungen"},
        {"Appearance Changes Notice", "Explorer muss für Änderungen neu gestartet werden"},
        {"No appearance changes requiring restart", "Keine Darstellungsänderungen, die einen Neustart erfordern"},
        {"Restart Explorer", "Explorer neu starten"},

        // Neue Darstellungs-Optimierungsnamen und Tooltips
        {"Hide Personalized Web Recommendations", "Personalisierte Web-Empfehlungen ausblenden"},
        {"Removes personalized website recommendations from the Start menu", "Entfernt personalisierte Website-Empfehlungen aus dem Startmenü"},

        {"Hide Recommended Section in Start Menu", "Abschnitt 'Empfohlen' im Startmenü ausblenden"},
        {"Completely removes the Recommended section from the Start menu", "Entfernt den Abschnitt 'Empfohlen' vollständig aus dem Startmenü"},

        {"Hide Clock in System Tray", "Uhr im Infobereich ausblenden"},
        {"Hides the system clock from the taskbar notification area", "Blendet die Systemuhr im Benachrichtigungsbereich der Taskleiste aus"},

        {"Hide Meet Now Icon", "Symbol 'Sofortbesprechung' ausblenden"},
        {"Removes the Meet Now (instant meeting) icon from the taskbar", "Entfernt das Symbol 'Sofortbesprechung' (Meet Now) aus der Taskleiste"},

        {"Disable All Balloon Notifications", "Alle Sprechblasenbenachrichtigungen deaktivieren"},
        {"Turns off all balloon notifications from the system tray", "Schaltet alle Sprechblasenbenachrichtigungen aus dem Infobereich aus"},

        {"Hide Details Pane in File Explorer", "Detailbereich im Datei-Explorer ausblenden"},
        {"Hides the details pane in File Explorer that shows file properties", "Blendet den Detailbereich im Datei-Explorer aus, der Dateieigenschaften anzeigt"},

        // Darstellungs-Optimierungsnamen und Tooltips
        {"Disable Bing Search in Start Menu", "Bing-Suche im Startmenü deaktivieren"},
        {"Controls whether the search box in the Windows Start menu performs Bing web searches", "Steuert, ob das Suchfeld im Windows-Startmenü Bing-Websuchen durchführt"},

        {"Center Taskbar Icons", "Taskleistensymbole zentrieren"},
        {"Controls whether taskbar icons are displayed centered or left-aligned", "Steuert, ob Taskleistensymbole zentriert oder linksbündig angezeigt werden"},

        {"Enable Dark Mode", "Dunklen Modus aktivieren"},
        {"Controls whether Windows uses dark theme. Applies to apps and system interface", "Steuert, ob Windows das dunkle Design verwendet. Gilt für Apps und die Systemoberfläche"},

        {"Show Detailed BSoD", "Detaillierten Bluescreen anzeigen"},
        {"Controls whether detailed technical information is displayed on blue screen errors", "Steuert, ob detaillierte technische Informationen bei Bluescreen-Fehlern angezeigt werden"},

        {"Enable Mouse Acceleration", "Mausbeschleunigung aktivieren"},
        {"When enabled, cursor movement is affected by the speed of your physical mouse movements", "Wenn aktiviert, wird die Cursorbewegung von der Geschwindigkeit Ihrer physischen Mausbewegungen beeinflusst"},

        {"Enable NumLock on Startup", "Num-Taste beim Start aktivieren"},
        {"Controls the state of the NumLock key when your computer starts", "Steuert den Status der Num-Taste beim Starten Ihres Computers"},

        {"Show Search Button in Taskbar", "Suchschaltfläche in der Taskleiste anzeigen"},
        {"When enabled, the search button is displayed in the taskbar", "Wenn aktiviert, wird die Suchschaltfläche in der Taskleiste angezeigt"},

        {"Show File Extensions", "Dateierweiterungen anzeigen"},
        {"When enabled, file extensions (.txt, .jpg, etc.) are made visible", "Wenn aktiviert, werden Dateierweiterungen (.txt, .jpg usw.) sichtbar gemacht"},

        {"Show Hidden Files", "Versteckte Dateien anzeigen"},
        {"When enabled, hidden files are displayed", "Wenn aktiviert, werden versteckte Dateien angezeigt"},

        {"Enable Snap Assist Flyout", "Andock-Assistent-Flyout aktivieren"},
        {"When enabled, helper flyout is displayed when hovering screen corners or during window snapping", "Wenn aktiviert, wird ein Hilfs-Flyout angezeigt, wenn Sie mit der Maus über Bildschirmecken fahren oder Fenster andocken"},

        {"Enable Snap Assist Suggestion", "Andock-Assistent-Vorschlag aktivieren"},
        {"When enabled, suggestions for other apps to fill remaining areas are shown during window snapping", "Wenn aktiviert, werden beim Andocken von Fenstern Vorschläge für andere Apps angezeigt, um verbleibende Bereiche zu füllen"},

        {"Enable Snap Window", "Fenster andocken aktivieren"},
        {"When enabled, you can snap windows by dragging them to the edges of the screen", "Wenn aktiviert, können Sie Fenster andocken, indem Sie sie an die Bildschirmränder ziehen"},

        {"Enable Sticky Keys", "Einrastfunktion aktivieren"},
        {"When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries", "Wenn aktiviert, wird die Einrastfunktion aktiviert - Die Einrastfunktion ist eine Barrierefreiheitsfunktion, die Benutzern mit körperlichen Behinderungen hilft oder Benutzern hilft, Verletzungen durch wiederholte Belastung zu reduzieren"},

        {"Show Task View Button in Taskbar", "Schaltfläche 'Aktive Anwendungen' in der Taskleiste anzeigen"},
        {"When enabled, the Task View button is displayed in the taskbar", "Wenn aktiviert, wird die Schaltfläche 'Aktive Anwendungen' in der Taskleiste angezeigt"},

        {"Show Verbose Messages During Logon", "Ausführliche Meldungen bei der Anmeldung anzeigen"},
        {"Shows detailed messages during login process for troubleshooting and diagnostics", "Zeigt detaillierte Meldungen während des Anmeldevorgangs zur Fehlerbehebung und Diagnose an"},

        {"Show Widgets Button in Taskbar", "Widgets-Schaltfläche in der Taskleiste anzeigen"},
        {"When enabled, the Widgets button is displayed in the taskbar", "Wenn aktiviert, wird die Widgets-Schaltfläche in der Taskleiste angezeigt"},

        {"Enable Classic Right-Click Menu", "Klassisches Rechtsklick-Menü aktivieren"},
        {"Shows old (compact) context menu when right-clicking in file explorer on Windows 11", "Zeigt das alte (kompakte) Kontextmenü an, wenn Sie im Datei-Explorer unter Windows 11 mit der rechten Maustaste klicken"},

        {"Remove Gallery from Navigation Pane", "Galerie aus dem Navigationsbereich entfernen"},
        {"Removes or adds the Gallery item from the navigation pane on the left side of File Explorer", "Entfernt oder fügt das Galerie-Element im Navigationsbereich auf der linken Seite des Datei-Explorers hinzu"},

        {"Restarts Windows Explorer to apply changes", "Startet den Windows Explorer neu, um Änderungen anzuwenden"},

        // Sicherheits-Tab
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Sicherheitseinstellungen"},

        // Sicherheits-Optimierungsnamen und Tooltips (Verwendung übersetzter englischer Schlüssel)
        {"Windows Defender'ı Etkinleştir", "Windows Defender aktivieren"},
        {"Windows Defender antivirüs servisi", "Windows Defender Antivirus-Dienst"},

        {"Gerçek Zamanlı Korumayı Etkinleştir", "Echtzeitschutz aktivieren"},
        {"Windows Defender'ın gerçek zamanlı koruma özelliği", "Echtzeitschutzfunktion von Windows Defender"},

        {"SmartScreen'i Etkinleştir", "SmartScreen aktivieren"},
        {"Microsoft SmartScreen filtreleme özelliği", "Microsoft SmartScreen-Filterfunktion"},

        {"Windows Güvenlik Duvarını Etkinleştir", "Windows-Firewall aktivieren"},
        {"Windows Güvenlik Duvarı servisi", "Windows-Firewall-Dienst"},

        {"UAC'yi Etkinleştir", "UAC aktivieren"},
        {"Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar", "Benutzerkontensteuerung (UAC) - erfordert Benutzerbestätigung für Aktionen, die Administratorrechte benötigen"},

        {"UAC Seviyesini Yükselt", "UAC-Stufe erhöhen"},
        {"UAC seviyesini yüksek ayara getirir", "Setzt die UAC-Stufe auf die hohe Einstellung"},

        {"Güvenli Masaüstünde UAC'yi Etkinleştir", "UAC auf sicherem Desktop aktivieren"},
        {"UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir", "Zeigt UAC-Dialoge auf einem sicheren Desktop an, auf den Malware nicht zugreifen kann"},

        {"Son Kullanıcı Adını Gizle", "Letzten Benutzernamen ausblenden"},
        {"Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez", "Zeigt den Namen des zuletzt angemeldeten Benutzers auf dem Windows-Anmeldebildschirm nicht an"},

        {"SMB1 Protokolünü Devre Dışı Bırak", "SMB1-Protokoll deaktivieren"},
        {"Güvenlik açığı bulunan eski SMB1 protokolünü kapatır", "Deaktiviert das anfällige alte SMB1-Protokoll"},

        {"LLMNR Protokolünü Devre Dışı Bırak", "LLMNR-Protokoll deaktivieren"},
        {"Link-Local Multicast Name Resolution protokolünü devre dışı bırakır", "Deaktiviert das Link-Local Multicast Name Resolution-Protokoll"},

        {"NBT-NS'yi Devre Dışı Bırak", "NBT-NS deaktivieren"},
        {"NetBIOS Name Service protokolünü devre dışı bırakır", "Deaktiviert das NetBIOS Name Service-Protokoll"},

        {"Uzak Masaüstü Güvenlik Seviyesini Yükselt", "Sicherheitsstufe für Remotedesktop erhöhen"},
        {"Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar", "Setzt die Sicherheitsstufe des Remotedesktopprotokolls (RDP) auf hoch"},

        {"RDP için NLA Kimlik Doğrulamasını Etkinleştir", "NLA-Authentifizierung für RDP aktivieren"},
        {"RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir", "Erfordert Authentifizierung auf Netzwerkebene (NLA) für RDP"},

        {"RDP Şifreleme Seviyesini Yükselt", "RDP-Verschlüsselungsstufe erhöhen"},
        {"RDP için şifreleme seviyesini yüksek olarak ayarlar", "Setzt die Verschlüsselungsstufe für RDP auf hoch"},

        {"AutoRun'u Devre Dışı Bırak", "AutoRun deaktivieren"},
        {"Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır", "Deaktiviert die AutoRun-Funktion auf Wechselmedien"},

        {"USB Depolamayı Etkinleştir", "USB-Speicher aktivieren"},
        {"USB depolama cihazlarını etkinleştirir veya devre dışı bırakır", "Aktiviert oder deaktiviert USB-Speichergeräte"},

        {"PowerShell Yürütme İlkesini Güvenli Yap", "PowerShell-Ausführungsrichtlinie sichern"},
        {"PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar", "Legt die Ausführungsrichtlinie für PowerShell-Skripts auf RemoteSigned fest"},

        {"PowerShell Komut Kaydetmeyi Etkinleştir", "PowerShell-Befehlsprotokollierung aktivieren"},
        {"PowerShell komut blokları için günlük kaydını etkinleştirir", "Aktiviert die Protokollierung für PowerShell-Befehlsblöcke"},

        {"Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir", "Skript-Host-Sicherheit aktivieren"},
        {"Windows Script Host güvenliğini etkinleştirir", "Aktiviert die Sicherheit von Windows Script Host"},

        {"Windows Update'i Etkinleştir", "Windows Update aktivieren"},
        {"Windows Update servisini etkinleştirir", "Aktiviert den Windows Update-Dienst"},

        {"Otomatik Güncellemeleri Etkinleştir", "Automatische Updates aktivieren"},
        {"Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar", "Ermöglicht Windows das automatische Herunterladen und Installieren von Updates"},

        {"WPAD Protokolünü Devre Dışı Bırak", "WPAD-Protokoll deaktivieren"},
        {"Web Proxy Auto-Discovery protokolünü devre dışı bırakır", "Deaktiviert das Web Proxy Auto-Discovery-Protokoll"},

        {"WinRM Şifresiz Trafiği Devre Dışı Bırak", "Unverschlüsselten WinRM-Verkehr deaktivieren"},
        {"Windows Remote Management için şifresiz trafiği engeller", "Blockiert unverschlüsselten Verkehr für Windows Remote Management"},

        // AppX-Pakete-Tab
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - AppX-Pakete"},
        {"Remove Selected Apps", "Ausgewählte Apps entfernen"},
        {"Select All", "Alle auswählen"},
        {"Deselect All", "Auswahl aufheben"},
        {"Search apps", "Apps suchen"},
        {"Removing apps...", "Apps werden entfernt..."},
        {"Successfully removed", "Erfolgreich entfernt"},
        {"application(s)", "Anwendung(en)"},
        {"No apps selected", "Keine Apps ausgewählt"},
        {"System Apps", "System-Apps"},
        {"Warning: System apps are essential for Windows", "Warnung: System-Apps sind für Windows unerlässlich"},
        {"Removing", "Wird entfernt"},

        // Einstellungen-Tab
        {"Windows Tweaker - Settings", "Windows Tweaker - Einstellungen"},

        // Info-Tab
        {"Windows Tweaker - About", "Windows Tweaker - Info"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "Ein umfassendes Optimierungs- und Anpassungstool für Windows 11"},
        {"Developer", "Entwickler"},
        {"Version", "Version"},
        {"License", "Lizenz"},

        // Dialog (Keine spezifischen Elemente aufgeführt)

        // Umschalter (Toggle)
        {"ToggleOn", "Ein"}, // Geändert von "Açık" / "On" / "Activé"
        {"ToggleOff", "Aus"} // Geändert von "Kapalı" / "Off" / "Désactivé"
    };
}