#pragma once
#include <string>
#include <map>

inline std::map<std::string, std::string> GetTurkishTranslations() {
    return {
        // Global
        {"Language", "Dil"},
        {"English", "İngilizce"},
        {"Turkish", "Türkçe"},
        {"German", "Almanca"},
        {"French", "Fransızca"},
        {"Spanish", "İspanyolca"},
        {"Change Language", "Dili Değiştir"},
        {"Select Language", "Dil Seç"},
        
        // Sekmeler
        {"Privacy", "Gizlilik"},
        {"Performance", "Performans"},
        {"Appearance", "Görünüm"},
        {"Security", "Güvenlik"},
        {"Settings", "Ayarlar"},
        {"About", "Hakkında"},
        {"AppX Packages", "AppX Paketleri"},
        
        // Privacy Tab
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Gizlilik Ayarları"},
        {"Enable All", "Tümünü Etkinleştir"},
        {"Disable All", "Tümünü Devre Dışı Bırak"},
        
        // New Privacy Tweak Names and Tooltips
        {"Clear Recent Files on Exit", "Çıkışta Son Dosyaları Temizle"},
        {"Clears the list of recently opened files when you exit Windows", "Windows'tan çıktığınızda son açılan dosyaların listesini temizler"},
        
        {"Disable Windows Copilot", "Windows Copilot'u Devre Dışı Bırak"},
        {"Disables Windows Copilot AI assistant", "Windows Copilot yapay zeka asistanını devre dışı bırakır"},
        
        // Privacy Tweak Names and Tooltips
        {"Disable Sync Provider Notifications in File Explorer", "Dosya Gezgini'nde Senkronizasyon Sağlayıcı Bildirimlerini Devre Dışı Bırak"},
        {"Disables file sync provider notifications in File Explorer", "Dosya Gezgini'nde dosya senkronizasyon sağlayıcı bildirimlerini devre dışı bırakır"},
        
        {"Disable Fun Facts and Tips on Lock Screen", "Kilit Ekranındaki Eğlenceli Bilgileri ve İpuçlarını Devre Dışı Bırak"},
        {"Disables fun facts, tips, tricks on your lock screen", "Kilit ekranınızdaki eğlenceli bilgileri, ipuçlarını ve püf noktaları devre dışı bırakır"},
        
        {"Disable Suggested Content in Settings", "Ayarlar'daki Önerilen İçeriği Devre Dışı Bırak"},
        {"Disables suggested content in the Settings app", "Ayarlar uygulamasındaki önerilen içeriği devre dışı bırakır"},
        
        {"Disable Tips and Suggestions When Using Windows", "Windows'u Kullanırken İpuçlarını ve Önerileri Devre Dışı Bırak"},
        {"Disables tips and suggestions when using Windows", "Windows'u kullanırken ipuçlarını ve önerileri devre dışı bırakır"},
        
        {"Disable 'Get the Most out of Windows' Suggestions", "'Windows'tan En İyi Şekilde Yararlanın' Önerilerini Devre Dışı Bırak"},
        {"Disables suggestions on how to get the most out of Windows and finish setting up the device", "Windows'tan en iyi şekilde yararlanma ve cihazı kurma hakkındaki önerileri devre dışı bırakır"},
        
        {"Disable Windows Welcome Experience", "Windows Karşılama Deneyimini Devre Dışı Bırak"},
        {"Disables the Windows welcome experience after updates and when signing in", "Güncellemelerden sonra ve oturum açarken Windows karşılama deneyimini devre dışı bırakır"},
        
        {"Disable Personalized Ads", "Kişiselleştirilmiş Reklamları Devre Dışı Bırak"},
        {"Prevents apps from showing personalized ads by using your advertising ID", "Uygulamaların reklam kimliğinizi kullanarak kişiselleştirilmiş reklamlar göstermesini engeller"},
        
        {"Disable Tailored Experiences", "Özelleştirilmiş Deneyimleri Devre Dışı Bırak"},
        {"Disables tailored experiences with diagnostic data", "Tanılama verileriyle özelleştirilmiş deneyimleri devre dışı bırakır"},
        
        {"Disable Recommendations in Start Menu", "Başlat Menüsündeki Önerileri Devre Dışı Bırak"},
        {"Disables recommendations for tips, shortcuts, new apps, and more in Start menu", "Başlat menüsünde ipuçları, kısayollar, yeni uygulamalar ve daha fazlası için önerileri devre dışı bırakır"},
        
        {"Disable Notification Suggestions", "Bildirim Önerilerini Devre Dışı Bırak"},
        {"Disables notification suggestions about unused apps", "Kullanılmayan uygulamalar hakkındaki bildirim önerilerini devre dışı bırakır"},
        
        {"Disable Bing Results in Windows Search", "Windows Arama'da Bing Sonuçlarını Devre Dışı Bırak"},
        {"Disables Bing results in Windows Search", "Windows Arama'da Bing sonuçlarını devre dışı bırakır"},
        
        {"Disable Edge Desktop Search Widget", "Edge Masaüstü Arama Widget'ını Devre Dışı Bırak"},
        {"Disables the Edge search widget on desktop", "Masaüstündeki Edge arama widget'ını devre dışı bırakır"},
        
        {"Disable Location Access", "Konum Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your location", "Uygulamaların konumunuza erişimini engeller"},
        
        {"Disable Camera Access", "Kamera Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your camera", "Uygulamaların kameranıza erişimini engeller"},
        
        {"Disable Microphone Access", "Mikrofon Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your microphone", "Uygulamaların mikrofonunuza erişimini engeller"},
        
        {"Disable Documents Library Access", "Belgeler Kitaplığı Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your documents library", "Uygulamaların belgeler kitaplığınıza erişimini engeller"},
        
        {"Disable Pictures Library Access", "Resimler Kitaplığı Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your pictures library", "Uygulamaların resimler kitaplığınıza erişimini engeller"},
        
        {"Disable Videos Library Access", "Videolar Kitaplığı Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your videos library", "Uygulamaların videolar kitaplığınıza erişimini engeller"},
        
        {"Disable Broad File System Access", "Geniş Dosya Sistemi Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing the file system broadly", "Uygulamaların dosya sistemine geniş erişimini engeller"},
        
        {"Disable Account Information Access", "Hesap Bilgilerine Erişimi Devre Dışı Bırak"},
        {"Prevents apps from accessing your name, picture, and account info", "Uygulamaların adınıza, resminize ve hesap bilgilerinize erişimini engeller"},
        
        {"Disable Contacts Access", "Kişiler Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your contacts", "Uygulamaların kişilerinize erişimini engeller"},
        
        {"Disable Call History Access", "Arama Geçmişi Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your call history", "Uygulamaların arama geçmişinize erişimini engeller"},
        
        {"Disable Messaging Access", "Mesajlaşma Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your messages", "Uygulamaların mesajlarınıza erişimini engeller"},
        
        {"Disable Notification Access", "Bildirim Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your notifications", "Uygulamaların bildirimlerinize erişimini engeller"},
        
        {"Disable Email Access", "E-posta Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your email", "Uygulamaların e-postanıza erişimini engeller"},
        
        {"Disable Tasks Access", "Görevler Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your user data tasks", "Uygulamaların kullanıcı veri görevlerinize erişimini engeller"},
        
        {"Disable Diagnostics Access", "Tanılama Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your diagnostic information", "Uygulamaların tanılama bilgilerinize erişimini engeller"},
        
        {"Disable Voice Activation", "Ses Aktivasyonunu Devre Dışı Bırak"},
        {"Disables voice activation for all apps", "Tüm uygulamalar için ses aktivasyonunu devre dışı bırakır"},
        
        {"Disable Calendar Access", "Takvim Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing your calendar appointments", "Uygulamaların takvim randevularınıza erişimini engeller"},
        
        {"Disable Motion Access", "Hareket Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing motion data", "Uygulamaların hareket verilerine erişimini engeller"},
        
        {"Disable Radio Access", "Radyo Erişimini Devre Dışı Bırak"},
        {"Prevents apps from accessing radio controls", "Uygulamaların radyo kontrollerine erişimini engeller"},
        
        {"Disable Activity Feed", "Etkinlik Akışını Devre Dışı Bırak"},
        {"Disables the Windows activity feed", "Windows etkinlik akışını devre dışı bırakır"},
        
        {"Disable Notification Center", "Bildirim Merkezini Devre Dışı Bırak"},
        {"Disables the Windows notification center", "Windows bildirim merkezini devre dışı bırakır"},
        
        {"Disable Xbox Screen Recording", "Xbox Ekran Kaydını Devre Dışı Bırak"},
        {"Disables the Xbox Game DVR feature", "Xbox Game DVR özelliğini devre dışı bırakır"},
        
        {"Disable Auto Map Downloads", "Otomatik Harita İndirmelerini Devre Dışı Bırak"},
        {"Prevents Windows from automatically downloading map data", "Windows'un otomatik olarak harita verilerini indirmesini engeller"},
        
        {"Disable Lock Screen Camera", "Kilit Ekranı Kamerasını Devre Dışı Bırak"},
        {"Disables the camera on the lock screen", "Kilit ekranındaki kamerayı devre dışı bırakır"},
        
        {"Disable Biometrics", "Biyometrik Özellikleri Devre Dışı Bırak"},
        {"Disables Windows biometric features (including Windows Hello)", "Windows biyometrik özelliklerini (Windows Hello dahil) devre dışı bırakır"},
        
        // Performance Tab
        {"Windows Tweaker - Performance Settings", "Windows Tweaker - Performans Ayarları"},
        
        // New Performance Tweak Names and Tooltips
        {"Enable Confirm File Delete Dialog", "Dosya Silme Onay Penceresini Etkinleştir"},
        {"Shows a confirmation dialog when deleting files", "Dosyaları silerken onay iletişim kutusu gösterir"},
        
        {"Permanently Delete Files (Skip Recycle Bin)", "Dosyaları Kalıcı Olarak Sil (Geri Dönüşüm Kutusunu Atla)"},
        {"Deletes files permanently without moving them to the Recycle Bin", "Dosyaları Geri Dönüşüm Kutusuna taşımadan kalıcı olarak siler"},
        
        // Performance Tweak Names and Tooltips
        {"Disable Fullscreen Optimizations", "Tam Ekran Optimizasyonlarını Devre Dışı Bırak"},
        {"Disables Windows fullscreen optimizations for better game performance", "Daha iyi oyun performansı için Windows tam ekran optimizasyonlarını devre dışı bırakır"},
        
        {"Disable Mouse Acceleration", "Fare Hızlandırmasını Devre Dışı Bırak"},
        {"Removes mouse acceleration for more consistent cursor movement", "Daha tutarlı imleç hareketi için fare hızlandırmasını kaldırır"},
        
        {"Disable Game Bar", "Oyun Çubuğunu Devre Dışı Bırak"},
        {"Disables Game Bar and related features to reduce overhead", "Gereksiz yükü azaltmak için Oyun Çubuğunu ve ilgili özellikleri devre dışı bırakır"},
        
        {"Disable Game Mode", "Oyun Modunu Devre Dışı Bırak"},
        {"Turns off Windows Game Mode which can cause issues with some games", "Bazı oyunlarda sorunlara neden olabilen Windows Oyun Modunu kapatır"},
        
        {"Activate Ultimate Performance Mode", "Nihai Performans Modunu Etkinleştir"},
        {"Activates the hidden Ultimate Performance power plan for maximum performance", "Maksimum performans için gizli Nihai Performans güç planını etkinleştirir"},
        
        {"Disable Hardware Accelerated GPU Scheduling", "Donanım Hızlandırmalı GPU Zamanlamasını Devre Dışı Bırak"},
        {"Disables HAGS which can cause issues with some systems", "Bazı sistemlerde sorunlara neden olabilen HAGS'yi devre dışı bırakır"},
        
        {"Limit Windows Defender Usage", "Windows Defender Kullanımını Sınırla"},
        {"Limits Windows Defender CPU usage for better performance", "Daha iyi performans için Windows Defender CPU kullanımını sınırlar"},
        
        {"Disable Core Isolation", "Çekirdek İzolasyonunu Devre Dışı Bırak"},
        {"Disables memory integrity for better performance (reduces security)", "Daha iyi performans için bellek bütünlüğünü devre dışı bırakır (güvenliği azaltır)"},
        
        {"Disable Prefetch", "Önbelleğe Almayı Devre Dışı Bırak"},
        {"Disables Windows Prefetch service to free up resources", "Kaynakları serbest bırakmak için Windows Prefetch hizmetini devre dışı bırakır"},
        
        {"Disable Storage Sense", "Depolama Duyarlılığını Devre Dışı Bırak"},
        {"Disables automatic disk cleanup to prevent background disk activity", "Arka plan disk etkinliğini önlemek için otomatik disk temizlemeyi devre dışı bırakır"},
        
        {"Disable Windows Search", "Windows Aramayı Devre Dışı Bırak"},
        {"Disables Windows Search indexing service to free up system resources", "Sistem kaynaklarını serbest bırakmak için Windows Arama indeksleme hizmetini devre dışı bırakır"},
        
        {"Disable Hibernation", "Hazırda Bekletmeyi Devre Dışı Bırak"},
        {"Disables system hibernation to free up disk space and resources", "Disk alanı ve kaynakları serbest bırakmak için sistem hazırda bekletme özelliğini devre dışı bırakır"},
        
        // Appearance Tab
        {"Windows Tweaker - Appearance Settings", "Windows Tweaker - Görünüm Ayarları"},
        {"Appearance Changes Notice", "Değişiklikler için Gezgin yeniden başlatılmalı"},
        {"No appearance changes requiring restart", "Yeniden başlatma gerektiren değişiklik yok"},
        {"Restart Explorer", "Gezgini Yeniden Başlat"},
        
        // New Appearance Tweak Names and Tooltips
        {"Hide Personalized Web Recommendations", "Kişiselleştirilmiş Web Önerilerini Gizle"},
        {"Removes personalized website recommendations from the Start menu", "Başlat menüsünden kişiselleştirilmiş web sitesi önerilerini kaldırır"},
        
        {"Hide Recommended Section in Start Menu", "Başlat Menüsünde Önerilen Bölümünü Gizle"},
        {"Completely removes the Recommended section from the Start menu", "Başlat menüsünden Önerilen bölümünü tamamen kaldırır"},
        
        {"Hide Clock in System Tray", "Sistem Tepsisinde Saati Gizle"},
        {"Hides the system clock from the taskbar notification area", "Görev çubuğu bildirim alanında sistem saatini gizler"},
        
        {"Hide Meet Now Icon", "Anında Toplantı Simgesini Gizle"},
        {"Removes the Meet Now (instant meeting) icon from the taskbar", "Görev çubuğundan Anında Toplantı simgesini kaldırır"},
        
        {"Disable All Balloon Notifications", "Tüm Balon Bildirimlerini Devre Dışı Bırak"},
        {"Turns off all balloon notifications from the system tray", "Sistem tepsisinden gelen tüm balon bildirimlerini kapatır"},
        
        {"Hide Details Pane in File Explorer", "Dosya Gezgini'nde Ayrıntılar Bölmesini Gizle"},
        {"Hides the details pane in File Explorer that shows file properties", "Dosya Gezgini'nde dosya özelliklerini gösteren ayrıntılar bölmesini gizler"},
        
        // Appearance Tweak Names and Tooltips
        {"Disable Bing Search in Start Menu", "Başlat Menüsünde Bing Aramayı Devre Dışı Bırak"},
        {"Controls whether the search box in the Windows Start menu performs Bing web searches", "Windows başlat menüsündeki arama kutusunun Bing ile web araması yapma özelliğini kontrol eder"},
        
        {"Center Taskbar Icons", "Görev Çubuğu Simgelerini Ortala"},
        {"Controls whether taskbar icons are displayed centered or left-aligned", "Görev çubuğu simgelerinin ortalı veya sola hizalı görüntülenmesini kontrol eder"},
        
        {"Enable Dark Mode", "Karanlık Modu Etkinleştir"},
        {"Controls whether Windows uses dark theme. Applies to apps and system interface", "Windows'un karanlık temayı kullanmasını kontrol eder. Uygulamalar ve sistem arayüzü için geçerlidir"},
        
        {"Show Detailed BSoD", "Detaylı Mavi Ekran Göster"},
        {"Controls whether detailed technical information is displayed on blue screen errors", "Mavi ekran hatalarında detaylı teknik bilgilerin görüntülenmesini kontrol eder"},
        
        {"Enable Mouse Acceleration", "Fare İvmesini Etkinleştir"},
        {"When enabled, cursor movement is affected by the speed of your physical mouse movements", "Etkinleştirildiğinde imleç hareketi, fiziksel fare hareketlerinizin hızından etkilenir"},
        
        {"Enable NumLock on Startup", "Başlangıçta NumLock Etkinleştir"},
        {"Controls the state of the NumLock key when your computer starts", "Bilgisayarınız başladığında NumLock tuşunun durumunu kontrol eder"},
        
        {"Show Search Button in Taskbar", "Görev Çubuğunda Arama Düğmesini Göster"},
        {"When enabled, the search button is displayed in the taskbar", "Etkinleştirildiğinde görev çubuğunda arama düğmesi görüntülenir"},
        
        {"Show File Extensions", "Dosya Uzantılarını Göster"},
        {"When enabled, file extensions (.txt, .jpg, etc.) are made visible", "Etkinleştirildiğinde dosya uzantıları (.txt, .jpg vb.) görünür olur"},
        
        {"Show Hidden Files", "Gizli Dosyaları Göster"},
        {"When enabled, hidden files are displayed", "Etkinleştirildiğinde gizli dosyalar gösterilir"},
        
        {"Enable Snap Assist Flyout", "Snap Assist Açılır Penceresini Etkinleştir"},
        {"When enabled, helper flyout is displayed when hovering screen corners or during window snapping", "Etkinleştirildiğinde, fare ekran köşelerine götürüldüğünde veya pencere yerleştirme işlemi sırasında yardım açılır penceresi gösterilir"},
        
        {"Enable Snap Assist Suggestion", "Snap Assist Önerisini Etkinleştir"},
        {"When enabled, suggestions for other apps to fill remaining areas are shown during window snapping", "Etkinleştirildiğinde, pencere yerleştirme işlemi sırasında boşta kalan alanlara yerleştirilebilecek diğer uygulama önerileri gösterilir"},
        
        {"Enable Snap Window", "Pencere Yerleştirmeyi Etkinleştir"},
        {"When enabled, you can snap windows by dragging them to the edges of the screen", "Etkinleştirildiğinde pencereleri sürükleyerek ekranın kenarlarına yerleştirebilirsiniz"},
        
        {"Enable Sticky Keys", "Yapışkan Tuşları Etkinleştir"},
        {"When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries", "Etkinleştirildiğinde Yapışkan Tuşlar özelliği aktifleştirilir - Yapışkan tuşlar, fiziksel engelli kullanıcılara yardımcı olan veya kullanıcıların tekrarlayan zorlanma yaralanmalarını azaltmasına yardımcı olan bir erişilebilirlik özelliğidir"},
        
        {"Show Task View Button in Taskbar", "Görev Çubuğunda Görev Görünümü Düğmesini Göster"},
        {"When enabled, the Task View button is displayed in the taskbar", "Etkinleştirildiğinde görev çubuğunda Görev Görünümü düğmesi gösterilir"},
        
        {"Show Verbose Messages During Logon", "Oturum Açma Sırasında Ayrıntılı Mesajlar Göster"},
        {"Shows detailed messages during login process for troubleshooting and diagnostics", "Sorun giderme ve tanılama için oturum açma işlemi sırasında ayrıntılı mesajları gösterir"},
        
        {"Show Widgets Button in Taskbar", "Görev Çubuğunda Widget Düğmesini Göster"},
        {"When enabled, the Widgets button is displayed in the taskbar", "Etkinleştirildiğinde görev çubuğunda Widget düğmesi gösterilir"},
        
        {"Enable Classic Right-Click Menu", "Klasik Sağ Tık Menüsünü Etkinleştir"},
        {"Shows old (compact) context menu when right-clicking in file explorer on Windows 11", "Windows 11'de dosya gezgininde sağ tıkladığınızda eski (kompakt) bağlam menüsünü gösterir"},
        
        {"Remove Gallery from Navigation Pane", "Galeriyi Gezgin Panelinden Kaldır"},
        {"Removes or adds the Gallery item from the navigation pane on the left side of File Explorer", "Dosya Gezgini'nin sol tarafındaki gezinti panelinden Galeri öğesini kaldırır veya ekler"},
        
        {"Restarts Windows Explorer to apply changes", "Değişiklikleri uygulamak için Windows Gezgini'ni yeniden başlatır"},
        
        // Security Tab
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Güvenlik Ayarları"},
        
        // Security Tweak Names and Tooltips
        {"Windows Defender'ı Etkinleştir", "Windows Defender'ı Etkinleştir"},
        {"Windows Defender antivirüs servisi", "Windows Defender antivirüs servisi"},
        
        {"Gerçek Zamanlı Korumayı Etkinleştir", "Gerçek Zamanlı Korumayı Etkinleştir"},
        {"Windows Defender'ın gerçek zamanlı koruma özelliği", "Windows Defender'ın gerçek zamanlı koruma özelliği"},
        
        {"SmartScreen'i Etkinleştir", "SmartScreen'i Etkinleştir"},
        {"Microsoft SmartScreen filtreleme özelliği", "Microsoft SmartScreen filtreleme özelliği"},
        
        {"Windows Güvenlik Duvarını Etkinleştir", "Windows Güvenlik Duvarını Etkinleştir"},
        {"Windows Güvenlik Duvarı servisi", "Windows Güvenlik Duvarı servisi"},
        
        {"UAC'yi Etkinleştir", "UAC'yi Etkinleştir"},
        {"Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar", "Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar"},
        
        {"UAC Seviyesini Yükselt", "UAC Seviyesini Yükselt"},
        {"UAC seviyesini yüksek ayara getirir", "UAC seviyesini yüksek ayara getirir"},
        
        {"Güvenli Masaüstünde UAC'yi Etkinleştir", "Güvenli Masaüstünde UAC'yi Etkinleştir"},
        {"UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir", "UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir"},
        
        {"Son Kullanıcı Adını Gizle", "Son Kullanıcı Adını Gizle"},
        {"Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez", "Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez"},
        
        {"SMB1 Protokolünü Devre Dışı Bırak", "SMB1 Protokolünü Devre Dışı Bırak"},
        {"Güvenlik açığı bulunan eski SMB1 protokolünü kapatır", "Güvenlik açığı bulunan eski SMB1 protokolünü kapatır"},
        
        {"LLMNR Protokolünü Devre Dışı Bırak", "LLMNR Protokolünü Devre Dışı Bırak"},
        {"Link-Local Multicast Name Resolution protokolünü devre dışı bırakır", "Link-Local Multicast Name Resolution protokolünü devre dışı bırakır"},
        
        {"NBT-NS'yi Devre Dışı Bırak", "NBT-NS'yi Devre Dışı Bırak"},
        {"NetBIOS Name Service protokolünü devre dışı bırakır", "NetBIOS Name Service protokolünü devre dışı bırakır"},
        
        {"Uzak Masaüstü Güvenlik Seviyesini Yükselt", "Uzak Masaüstü Güvenlik Seviyesini Yükselt"},
        {"Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar", "Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar"},
        
        {"RDP için NLA Kimlik Doğrulamasını Etkinleştir", "RDP için NLA Kimlik Doğrulamasını Etkinleştir"},
        {"RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir", "RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir"},
        
        {"RDP Şifreleme Seviyesini Yükselt", "RDP Şifreleme Seviyesini Yükselt"},
        {"RDP için şifreleme seviyesini yüksek olarak ayarlar", "RDP için şifreleme seviyesini yüksek olarak ayarlar"},
        
        {"AutoRun'u Devre Dışı Bırak", "AutoRun'u Devre Dışı Bırak"},
        {"Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır", "Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır"},
        
        {"USB Depolamayı Etkinleştir", "USB Depolamayı Etkinleştir"},
        {"USB depolama cihazlarını etkinleştirir veya devre dışı bırakır", "USB depolama cihazlarını etkinleştirir veya devre dışı bırakır"},
        
        {"PowerShell Yürütme İlkesini Güvenli Yap", "PowerShell Yürütme İlkesini Güvenli Yap"},
        {"PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar", "PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar"},
        
        {"PowerShell Komut Kaydetmeyi Etkinleştir", "PowerShell Komut Kaydetmeyi Etkinleştir"},
        {"PowerShell komut blokları için günlük kaydını etkinleştirir", "PowerShell komut blokları için günlük kaydını etkinleştirir"},
        
        {"Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir", "Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir"},
        {"Windows Script Host güvenliğini etkinleştirir", "Windows Script Host güvenliğini etkinleştirir"},
        
        {"Windows Update'i Etkinleştir", "Windows Update'i Etkinleştir"},
        {"Windows Update servisini etkinleştirir", "Windows Güncelleştirme servisini etkinleştirir"},
        
        {"Otomatik Güncellemeleri Etkinleştir", "Otomatik Güncellemeleri Etkinleştir"},
        {"Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar", "Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar"},
        
        {"WPAD Protokolünü Devre Dışı Bırak", "WPAD Protokolünü Devre Dışı Bırak"},
        {"Web Proxy Auto-Discovery protokolünü devre dışı bırakır", "Web Proxy Auto-Discovery protokolünü devre dışı bırakır"},
        
        {"WinRM Şifresiz Trafiği Devre Dışı Bırak", "WinRM Şifresiz Trafiği Devre Dışı Bırak"},
        {"Windows Remote Management için şifresiz trafiği engeller", "Windows Remote Management için şifresiz trafiği engeller"},
        
        // AppX Packages Tab
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - AppX Paketleri"},
        {"Remove Selected Apps", "Seçili Uygulamaları Kaldır"},
        {"Select All", "Tümünü Seç"},
        {"Deselect All", "Seçimi Kaldır"},
        {"Search apps", "Uygulama ara"},
        {"Removing apps...", "Uygulamalar kaldırılıyor..."},
        {"Successfully removed", "Başarıyla kaldırıldı"},
        {"application(s)", "uygulama(lar)"},
        {"No apps selected", "Seçili uygulama yok"},
        {"System Apps", "Sistem Uygulamaları"},
        {"Warning: System apps are essential for Windows", "Uyarı: Sistem uygulamaları Windows için gereklidir"},
        {"Removing", "Kaldırılıyor"},
        
        // Settings Tab
        {"Windows Tweaker - Settings", "Windows Tweaker - Ayarlar"},
        
        // About Tab
        {"Windows Tweaker - About", "Windows Tweaker - Hakkında"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "Kapsamlı bir Windows 11 optimizasyon ve özelleştirme aracı"},
        {"Developer", "Geliştirici"},
        {"Version", "Sürüm"},
        {"License", "Lisans"},
        
        // Dialog
        
        // Toggle
        {"ToggleOn", "Açık"},
        {"ToggleOff", "Kapalı"}
    };
} 