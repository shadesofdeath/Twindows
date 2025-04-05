#pragma once
#include <string>
#include <map>

// Fonction renommée pour refléter qu'elle retourne maintenant les traductions françaises
inline std::map<std::string, std::string> GetFrenchTranslations() {
    return {
        // Global
        {"Language", "Langue"},
        {"English", "Anglais"},
        {"Turkish", "Turc"},
        {"German", "Allemand"},
        {"French", "Français"},
        {"Spanish", "Espagnol"},
        {"Change Language", "Changer de langue"},
        {"Select Language", "Sélectionner la langue"},

        // Onglets (Sekmeler)
        {"Privacy", "Confidentialité"},
        {"Performance", "Performance"},
        {"Appearance", "Apparence"},
        {"Security", "Sécurité"},
        {"Settings", "Paramètres"},
        {"About", "À propos"},
        {"AppX Packages", "Packages AppX"},

        // Onglet Confidentialité
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Paramètres de confidentialité"},
        {"Enable All", "Tout activer"},
        {"Disable All", "Tout désactiver"},

        // Nouveaux noms et infobulles des ajustements de confidentialité
        {"Clear Recent Files on Exit", "Effacer les fichiers récents à la fermeture"},
        {"Clears the list of recently opened files when you exit Windows", "Efface la liste des fichiers récemment ouverts lorsque vous quittez Windows"},

        {"Disable Windows Copilot", "Désactiver Windows Copilot"},
        {"Disables Windows Copilot AI assistant", "Désactive l'assistant IA Windows Copilot"},

        // Noms et infobulles des ajustements de confidentialité
        {"Disable Sync Provider Notifications in File Explorer", "Désactiver les notifications du fournisseur de synchronisation dans l'Explorateur de fichiers"},
        {"Disables file sync provider notifications in File Explorer", "Désactive les notifications du fournisseur de synchronisation de fichiers dans l'Explorateur de fichiers"},

        {"Disable Fun Facts and Tips on Lock Screen", "Désactiver les anecdotes et astuces sur l'écran de verrouillage"},
        {"Disables fun facts, tips, tricks on your lock screen", "Désactive les anecdotes, astuces et conseils sur votre écran de verrouillage"},

        {"Disable Suggested Content in Settings", "Désactiver le contenu suggéré dans les Paramètres"},
        {"Disables suggested content in the Settings app", "Désactive le contenu suggéré dans l'application Paramètres"},

        {"Disable Tips and Suggestions When Using Windows", "Désactiver les conseils et suggestions lors de l'utilisation de Windows"},
        {"Disables tips and suggestions when using Windows", "Désactive les conseils et suggestions lors de l'utilisation de Windows"},

        {"Disable 'Get the Most out of Windows' Suggestions", "Désactiver les suggestions 'Tirez le meilleur parti de Windows'"},
        {"Disables suggestions on how to get the most out of Windows and finish setting up the device", "Désactive les suggestions sur la manière de tirer le meilleur parti de Windows et de terminer la configuration de l'appareil"},

        {"Disable Windows Welcome Experience", "Désactiver l'expérience d'accueil de Windows"},
        {"Disables the Windows welcome experience after updates and when signing in", "Désactive l'expérience d'accueil de Windows après les mises à jour et lors de la connexion"},

        {"Disable Personalized Ads", "Désactiver les publicités personnalisées"},
        {"Prevents apps from showing personalized ads by using your advertising ID", "Empêche les applications d'afficher des publicités personnalisées en utilisant votre identifiant publicitaire"},

        {"Disable Tailored Experiences", "Désactiver les expériences personnalisées"},
        {"Disables tailored experiences with diagnostic data", "Désactive les expériences personnalisées avec les données de diagnostic"},

        {"Disable Recommendations in Start Menu", "Désactiver les recommandations dans le menu Démarrer"},
        {"Disables recommendations for tips, shortcuts, new apps, and more in Start menu", "Désactive les recommandations de conseils, raccourcis, nouvelles applications, etc. dans le menu Démarrer"},

        {"Disable Notification Suggestions", "Désactiver les suggestions de notification"},
        {"Disables notification suggestions about unused apps", "Désactive les suggestions de notification concernant les applications inutilisées"},

        {"Disable Bing Results in Windows Search", "Désactiver les résultats Bing dans la recherche Windows"},
        {"Disables Bing results in Windows Search", "Désactive les résultats Bing dans la recherche Windows"},

        {"Disable Edge Desktop Search Widget", "Désactiver le widget de recherche de bureau Edge"},
        {"Disables the Edge search widget on desktop", "Désactive le widget de recherche Edge sur le bureau"},

        {"Disable Location Access", "Désactiver l'accès à la localisation"},
        {"Prevents apps from accessing your location", "Empêche les applications d'accéder à votre localisation"},

        {"Disable Camera Access", "Désactiver l'accès à la caméra"},
        {"Prevents apps from accessing your camera", "Empêche les applications d'accéder à votre caméra"},

        {"Disable Microphone Access", "Désactiver l'accès au microphone"},
        {"Prevents apps from accessing your microphone", "Empêche les applications d'accéder à votre microphone"},

        {"Disable Documents Library Access", "Désactiver l'accès à la bibliothèque Documents"},
        {"Prevents apps from accessing your documents library", "Empêche les applications d'accéder à votre bibliothèque Documents"},

        {"Disable Pictures Library Access", "Désactiver l'accès à la bibliothèque Images"},
        {"Prevents apps from accessing your pictures library", "Empêche les applications d'accéder à votre bibliothèque Images"},

        {"Disable Videos Library Access", "Désactiver l'accès à la bibliothèque Vidéos"},
        {"Prevents apps from accessing your videos library", "Empêche les applications d'accéder à votre bibliothèque Vidéos"},

        {"Disable Broad File System Access", "Désactiver l'accès étendu au système de fichiers"},
        {"Prevents apps from accessing the file system broadly", "Empêche les applications d'accéder largement au système de fichiers"},

        {"Disable Account Information Access", "Désactiver l'accès aux informations du compte"},
        {"Prevents apps from accessing your name, picture, and account info", "Empêche les applications d'accéder à votre nom, photo et informations de compte"},

        {"Disable Contacts Access", "Désactiver l'accès aux contacts"},
        {"Prevents apps from accessing your contacts", "Empêche les applications d'accéder à vos contacts"},

        {"Disable Call History Access", "Désactiver l'accès à l'historique des appels"},
        {"Prevents apps from accessing your call history", "Empêche les applications d'accéder à votre historique des appels"},

        {"Disable Messaging Access", "Désactiver l'accès à la messagerie"},
        {"Prevents apps from accessing your messages", "Empêche les applications d'accéder à vos messages"},

        {"Disable Notification Access", "Désactiver l'accès aux notifications"},
        {"Prevents apps from accessing your notifications", "Empêche les applications d'accéder à vos notifications"},

        {"Disable Email Access", "Désactiver l'accès à l'e-mail"},
        {"Prevents apps from accessing your email", "Empêche les applications d'accéder à vos e-mails"},

        {"Disable Tasks Access", "Désactiver l'accès aux tâches"},
        {"Prevents apps from accessing your user data tasks", "Empêche les applications d'accéder à vos tâches de données utilisateur"},

        {"Disable Diagnostics Access", "Désactiver l'accès aux diagnostics"},
        {"Prevents apps from accessing your diagnostic information", "Empêche les applications d'accéder à vos informations de diagnostic"},

        {"Disable Voice Activation", "Désactiver l'activation vocale"},
        {"Disables voice activation for all apps", "Désactive l'activation vocale pour toutes les applications"},

        {"Disable Calendar Access", "Désactiver l'accès au calendrier"},
        {"Prevents apps from accessing your calendar appointments", "Empêche les applications d'accéder à vos rendez-vous de calendrier"},

        {"Disable Motion Access", "Désactiver l'accès aux mouvements"},
        {"Prevents apps from accessing motion data", "Empêche les applications d'accéder aux données de mouvement"},

        {"Disable Radio Access", "Désactiver l'accès aux radios"},
        {"Prevents apps from accessing radio controls", "Empêche les applications d'accéder aux contrôles radio"},

        {"Disable Activity Feed", "Désactiver le flux d'activité"},
        {"Disables the Windows activity feed", "Désactive le flux d'activité Windows"},

        {"Disable Notification Center", "Désactiver le Centre de notifications"},
        {"Disables the Windows notification center", "Désactive le centre de notifications Windows"},

        {"Disable Xbox Screen Recording", "Désactiver l'enregistrement d'écran Xbox"},
        {"Disables the Xbox Game DVR feature", "Désactive la fonctionnalité Xbox Game DVR"},

        {"Disable Auto Map Downloads", "Désactiver le téléchargement automatique des cartes"},
        {"Prevents Windows from automatically downloading map data", "Empêche Windows de télécharger automatiquement les données cartographiques"},

        {"Disable Lock Screen Camera", "Désactiver la caméra de l'écran de verrouillage"},
        {"Disables the camera on the lock screen", "Désactive la caméra sur l'écran de verrouillage"},

        {"Disable Biometrics", "Désactiver la biométrie"},
        {"Disables Windows biometric features (including Windows Hello)", "Désactive les fonctionnalités biométriques de Windows (y compris Windows Hello)"},

        // Onglet Performance
        {"Windows Tweaker - Performance Settings", "Windows Tweaker - Paramètres de performance"},

        // Nouveaux noms et infobulles des ajustements de performance
        {"Enable Confirm File Delete Dialog", "Activer la boîte de dialogue de confirmation de suppression de fichier"},
        {"Shows a confirmation dialog when deleting files", "Affiche une boîte de dialogue de confirmation lors de la suppression de fichiers"},

        {"Permanently Delete Files (Skip Recycle Bin)", "Supprimer définitivement les fichiers (Ignorer la Corbeille)"},
        {"Deletes files permanently without moving them to the Recycle Bin", "Supprime définitivement les fichiers sans les déplacer dans la Corbeille"},

        // Noms et infobulles des ajustements de performance
        {"Disable Fullscreen Optimizations", "Désactiver les optimisations plein écran"},
        {"Disables Windows fullscreen optimizations for better game performance", "Désactive les optimisations plein écran de Windows pour de meilleures performances de jeu"},

        {"Disable Mouse Acceleration", "Désactiver l'accélération de la souris"},
        {"Removes mouse acceleration for more consistent cursor movement", "Supprime l'accélération de la souris pour un mouvement de curseur plus cohérent"},

        {"Disable Game Bar", "Désactiver la barre de jeux"},
        {"Disables Game Bar and related features to reduce overhead", "Désactive la barre de jeux et les fonctionnalités associées pour réduire la surcharge"},

        {"Disable Game Mode", "Désactiver le mode Jeu"},
        {"Turns off Windows Game Mode which can cause issues with some games", "Désactive le mode Jeu de Windows qui peut causer des problèmes avec certains jeux"},

        {"Activate Ultimate Performance Mode", "Activer le mode Performances ultimes"},
        {"Activates the hidden Ultimate Performance power plan for maximum performance", "Active le plan d'alimentation Performances ultimes caché pour des performances maximales"},

        {"Disable Hardware Accelerated GPU Scheduling", "Désactiver la planification GPU accélérée par matériel"},
        {"Disables HAGS which can cause issues with some systems", "Désactive HAGS qui peut causer des problèmes avec certains systèmes"},

        {"Limit Windows Defender Usage", "Limiter l'utilisation de Windows Defender"},
        {"Limits Windows Defender CPU usage for better performance", "Limite l'utilisation du processeur par Windows Defender pour de meilleures performances"},

        {"Disable Core Isolation", "Désactiver l'isolation du noyau"},
        {"Disables memory integrity for better performance (reduces security)", "Désactive l'intégrité de la mémoire pour de meilleures performances (réduit la sécurité)"},

        {"Disable Prefetch", "Désactiver Prefetch"},
        {"Disables Windows Prefetch service to free up resources", "Désactive le service Windows Prefetch pour libérer des ressources"},

        {"Disable Storage Sense", "Désactiver l'Assistant Stockage"},
        {"Disables automatic disk cleanup to prevent background disk activity", "Désactive le nettoyage automatique du disque pour éviter l'activité disque en arrière-plan"},

        {"Disable Windows Search", "Désactiver Windows Search"},
        {"Disables Windows Search indexing service to free up system resources", "Désactive le service d'indexation Windows Search pour libérer des ressources système"},

        {"Disable Hibernation", "Désactiver la mise en veille prolongée"},
        {"Disables system hibernation to free up disk space and resources", "Désactive la mise en veille prolongée du système pour libérer de l'espace disque et des ressources"},

        // Onglet Apparence
        {"Windows Tweaker - Appearance Settings", "Windows Tweaker - Paramètres d'apparence"},
        {"Appearance Changes Notice", "L'Explorateur doit être redémarré pour appliquer les modifications"},
        {"No appearance changes requiring restart", "Aucun changement d'apparence ne nécessite de redémarrage"},
        {"Restart Explorer", "Redémarrer l'Explorateur"},

        // Nouveaux noms et infobulles des ajustements d'apparence
        {"Hide Personalized Web Recommendations", "Masquer les recommandations Web personnalisées"},
        {"Removes personalized website recommendations from the Start menu", "Supprime les recommandations de sites Web personnalisés du menu Démarrer"},

        {"Hide Recommended Section in Start Menu", "Masquer la section Recommandé dans le menu Démarrer"},
        {"Completely removes the Recommended section from the Start menu", "Supprime complètement la section Recommandé du menu Démarrer"},

        {"Hide Clock in System Tray", "Masquer l'horloge dans la zone de notification"},
        {"Hides the system clock from the taskbar notification area", "Masque l'horloge système de la zone de notification de la barre des tâches"},

        {"Hide Meet Now Icon", "Masquer l'icône Visioconférence instantanée"},
        {"Removes the Meet Now (instant meeting) icon from the taskbar", "Supprime l'icône Visioconférence instantanée (Meet Now) de la barre des tâches"},

        {"Disable All Balloon Notifications", "Désactiver toutes les notifications bulles"},
        {"Turns off all balloon notifications from the system tray", "Désactive toutes les notifications bulles de la zone de notification système"},

        {"Hide Details Pane in File Explorer", "Masquer le volet Détails dans l'Explorateur de fichiers"},
        {"Hides the details pane in File Explorer that shows file properties", "Masque le volet des détails dans l'Explorateur de fichiers qui affiche les propriétés du fichier"},

        // Noms et infobulles des ajustements d'apparence
        {"Disable Bing Search in Start Menu", "Désactiver la recherche Bing dans le menu Démarrer"},
        {"Controls whether the search box in the Windows Start menu performs Bing web searches", "Contrôle si la zone de recherche du menu Démarrer de Windows effectue des recherches Web Bing"},

        {"Center Taskbar Icons", "Centrer les icônes de la barre des tâches"},
        {"Controls whether taskbar icons are displayed centered or left-aligned", "Contrôle si les icônes de la barre des tâches sont affichées centrées ou alignées à gauche"},

        {"Enable Dark Mode", "Activer le mode sombre"},
        {"Controls whether Windows uses dark theme. Applies to apps and system interface", "Contrôle si Windows utilise le thème sombre. S'applique aux applications et à l'interface système"},

        {"Show Detailed BSoD", "Afficher l'écran bleu détaillé (BSoD)"},
        {"Controls whether detailed technical information is displayed on blue screen errors", "Contrôle si des informations techniques détaillées sont affichées sur les erreurs d'écran bleu"},

        {"Enable Mouse Acceleration", "Activer l'accélération de la souris"},
        {"When enabled, cursor movement is affected by the speed of your physical mouse movements", "Lorsque activé, le mouvement du curseur est affecté par la vitesse de vos mouvements physiques de souris"},

        {"Enable NumLock on Startup", "Activer Verr Num au démarrage"},
        {"Controls the state of the NumLock key when your computer starts", "Contrôle l'état de la touche Verr Num au démarrage de votre ordinateur"},

        {"Show Search Button in Taskbar", "Afficher le bouton Recherche dans la barre des tâches"},
        {"When enabled, the search button is displayed in the taskbar", "Lorsque activé, le bouton de recherche est affiché dans la barre des tâches"},

        {"Show File Extensions", "Afficher les extensions de fichier"},
        {"When enabled, file extensions (.txt, .jpg, etc.) are made visible", "Lorsque activé, les extensions de fichier (.txt, .jpg, etc.) sont rendues visibles"},

        {"Show Hidden Files", "Afficher les fichiers cachés"},
        {"When enabled, hidden files are displayed", "Lorsque activé, les fichiers cachés sont affichés"},

        {"Enable Snap Assist Flyout", "Activer le menu volant de l'Assistant Ancrage"},
        {"When enabled, helper flyout is displayed when hovering screen corners or during window snapping", "Lorsque activé, un menu volant d'aide s'affiche lors du survol des coins de l'écran ou lors de l'ancrage de fenêtres"},

        {"Enable Snap Assist Suggestion", "Activer la suggestion de l'Assistant Ancrage"},
        {"When enabled, suggestions for other apps to fill remaining areas are shown during window snapping", "Lorsque activé, des suggestions d'autres applications pour remplir les zones restantes sont affichées lors de l'ancrage de fenêtres"},

        {"Enable Snap Window", "Activer l'ancrage des fenêtres"},
        {"When enabled, you can snap windows by dragging them to the edges of the screen", "Lorsque activé, vous pouvez ancrer les fenêtres en les faisant glisser vers les bords de l'écran"},

        {"Enable Sticky Keys", "Activer les touches rémanentes"},
        {"When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries", "Lorsque activé, la fonction Touches rémanentes est activée - Les Touches rémanentes sont une fonction d'accessibilité qui aide les utilisateurs ayant des handicaps physiques ou aide les utilisateurs à réduire les microtraumatismes répétés"},

        {"Show Task View Button in Taskbar", "Afficher le bouton Affichage des tâches dans la barre des tâches"},
        {"When enabled, the Task View button is displayed in the taskbar", "Lorsque activé, le bouton Affichage des tâches est affiché dans la barre des tâches"},

        {"Show Verbose Messages During Logon", "Afficher les messages détaillés lors de la connexion"},
        {"Shows detailed messages during login process for troubleshooting and diagnostics", "Affiche des messages détaillés pendant le processus de connexion pour le dépannage et les diagnostics"},

        {"Show Widgets Button in Taskbar", "Afficher le bouton Widgets dans la barre des tâches"},
        {"When enabled, the Widgets button is displayed in the taskbar", "Lorsque activé, le bouton Widgets est affiché dans la barre des tâches"},

        {"Enable Classic Right-Click Menu", "Activer le menu contextuel classique"},
        {"Shows old (compact) context menu when right-clicking in file explorer on Windows 11", "Affiche l'ancien menu contextuel (compact) lors d'un clic droit dans l'explorateur de fichiers sous Windows 11"},

        {"Remove Gallery from Navigation Pane", "Supprimer Galerie du volet de navigation"},
        {"Removes or adds the Gallery item from the navigation pane on the left side of File Explorer", "Supprime ou ajoute l'élément Galerie du volet de navigation sur le côté gauche de l'Explorateur de fichiers"},

        {"Restarts Windows Explorer to apply changes", "Redémarre l'Explorateur Windows pour appliquer les modifications"},

        // Onglet Sécurité
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Paramètres de sécurité"},

        // Noms et infobulles des ajustements de sécurité (Utilisation des clés anglaises traduites)
        {"Windows Defender'ı Etkinleştir", "Activer Windows Defender"},
        {"Windows Defender antivirüs servisi", "Service antivirus Windows Defender"},

        {"Gerçek Zamanlı Korumayı Etkinleştir", "Activer la protection en temps réel"},
        {"Windows Defender'ın gerçek zamanlı koruma özelliği", "Fonction de protection en temps réel de Windows Defender"},

        {"SmartScreen'i Etkinleştir", "Activer SmartScreen"},
        {"Microsoft SmartScreen filtreleme özelliği", "Fonction de filtrage Microsoft SmartScreen"},

        {"Windows Güvenlik Duvarını Etkinleştir", "Activer le Pare-feu Windows"},
        {"Windows Güvenlik Duvarı servisi", "Service du Pare-feu Windows"},

        {"UAC'yi Etkinleştir", "Activer l'UAC"},
        {"Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar", "Contrôle de compte d'utilisateur (UAC) - requiert la confirmation de l'utilisateur pour les actions nécessitant des privilèges d'administrateur"},

        {"UAC Seviyesini Yükselt", "Élever le niveau UAC"},
        {"UAC seviyesini yüksek ayara getirir", "Règle le niveau UAC sur le paramètre élevé"},

        {"Güvenli Masaüstünde UAC'yi Etkinleştir", "Activer l'UAC sur le Bureau sécurisé"},
        {"UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir", "Affiche les boîtes de dialogue UAC sur un bureau sécurisé inaccessible aux logiciels malveillants"},

        {"Son Kullanıcı Adını Gizle", "Masquer le dernier nom d'utilisateur"},
        {"Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez", "N'affiche pas le nom du dernier utilisateur connecté sur l'écran de connexion Windows"},

        {"SMB1 Protokolünü Devre Dışı Bırak", "Désactiver le protocole SMB1"},
        {"Güvenlik açığı bulunan eski SMB1 protokolünü kapatır", "Désactive l'ancien protocole SMB1 vulnérable"},

        {"LLMNR Protokolünü Devre Dışı Bırak", "Désactiver le protocole LLMNR"},
        {"Link-Local Multicast Name Resolution protokolünü devre dışı bırakır", "Désactive le protocole Link-Local Multicast Name Resolution"},

        {"NBT-NS'yi Devre Dışı Bırak", "Désactiver NBT-NS"},
        {"NetBIOS Name Service protokolünü devre dışı bırakır", "Désactive le protocole NetBIOS Name Service"},

        {"Uzak Masaüstü Güvenlik Seviyesini Yükselt", "Élever le niveau de sécurité du Bureau à distance"},
        {"Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar", "Règle le niveau de sécurité du Protocole Bureau à distance (RDP) sur élevé"},

        {"RDP için NLA Kimlik Doğrulamasını Etkinleştir", "Activer l'authentification NLA pour RDP"},
        {"RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir", "Requiert l'authentification au niveau du réseau (NLA) pour RDP"},

        {"RDP Şifreleme Seviyesini Yükselt", "Élever le niveau de chiffrement RDP"},
        {"RDP için şifreleme seviyesini yüksek olarak ayarlar", "Règle le niveau de chiffrement pour RDP sur élevé"},

        {"AutoRun'u Devre Dışı Bırak", "Désactiver l'exécution automatique (AutoRun)"},
        {"Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır", "Désactive la fonction d'exécution automatique sur les supports amovibles"},

        {"USB Depolamayı Etkinleştir", "Activer le stockage USB"},
        {"USB depolama cihazlarını etkinleştirir veya devre dışı bırakır", "Active ou désactive les périphériques de stockage USB"},

        {"PowerShell Yürütme İlkesini Güvenli Yap", "Sécuriser la stratégie d'exécution PowerShell"},
        {"PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar", "Définit la stratégie d'exécution pour les scripts PowerShell sur RemoteSigned"},

        {"PowerShell Komut Kaydetmeyi Etkinleştir", "Activer la journalisation des commandes PowerShell"},
        {"PowerShell komut blokları için günlük kaydını etkinleştirir", "Active la journalisation pour les blocs de commandes PowerShell"},

        {"Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir", "Activer la sécurité de l'hôte de script"},
        {"Windows Script Host güvenliğini etkinleştirir", "Active la sécurité de Windows Script Host"},

        {"Windows Update'i Etkinleştir", "Activer Windows Update"},
        {"Windows Update servisini etkinleştirir", "Active le service Windows Update"},

        {"Otomatik Güncellemeleri Etkinleştir", "Activer les mises à jour automatiques"},
        {"Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar", "Permet à Windows de télécharger et d'installer automatiquement les mises à jour"},

        {"WPAD Protokolünü Devre Dışı Bırak", "Désactiver le protocole WPAD"},
        {"Web Proxy Auto-Discovery protokolünü devre dışı bırakır", "Désactive le protocole Web Proxy Auto-Discovery"},

        {"WinRM Şifresiz Trafiği Devre Dışı Bırak", "Désactiver le trafic WinRM non chiffré"},
        {"Windows Remote Management için şifresiz trafiği engeller", "Bloque le trafic non chiffré pour Windows Remote Management"},

        // Onglet Packages AppX
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - Packages AppX"},
        {"Remove Selected Apps", "Supprimer les applications sélectionnées"},
        {"Select All", "Tout sélectionner"},
        {"Deselect All", "Tout désélectionner"},
        {"Search apps", "Rechercher des applications"},
        {"Removing apps...", "Suppression des applications..."},
        {"Successfully removed", "Supprimé avec succès"},
        {"application(s)", "application(s)"},
        {"No apps selected", "Aucune application sélectionnée"},
        {"System Apps", "Applications système"},
        {"Warning: System apps are essential for Windows", "Avertissement : Les applications système sont essentielles pour Windows"},
        {"Removing", "Suppression en cours"},

        // Onglet Paramètres
        {"Windows Tweaker - Settings", "Windows Tweaker - Paramètres"},

        // Onglet À propos
        {"Windows Tweaker - About", "Windows Tweaker - À propos"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "Un outil complet d'optimisation et de personnalisation de Windows 11"},
        {"Developer", "Développeur"},
        {"Version", "Version"},
        {"License", "Licence"},

        // Dialogue (Aucun élément spécifique listé)

        // Bascule (Toggle)
        {"ToggleOn", "Activé"}, // Changé de "Açık" / "On"
        {"ToggleOff", "Désactivé"} // Changé de "Kapalı" / "Off"
    };
}