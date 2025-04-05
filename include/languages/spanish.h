#pragma once
#include <string>
#include <map>

// Función renombrada para reflejar que ahora devuelve traducciones al español
inline std::map<std::string, std::string> GetSpanishTranslations() {
    return {
        // Global
        {"Language", "Idioma"},
        {"English", "Inglés"},
        {"Turkish", "Turco"},
        {"German", "Alemán"},
        {"French", "Francés"},
        {"Spanish", "Español"},
        {"Change Language", "Cambiar idioma"},
        {"Select Language", "Seleccionar idioma"},

        // Pestañas (Sekmeler)
        {"Privacy", "Privacidad"},
        {"Performance", "Rendimiento"},
        {"Appearance", "Apariencia"},
        {"Security", "Seguridad"},
        {"Settings", "Configuración"},
        {"About", "Acerca de"},
        {"AppX Packages", "Paquetes AppX"},

        // Pestaña Privacidad
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Configuración de privacidad"},
        {"Enable All", "Habilitar todo"},
        {"Disable All", "Deshabilitar todo"},

        // Nuevos nombres y descripciones de ajustes de privacidad
        {"Clear Recent Files on Exit", "Borrar archivos recientes al salir"},
        {"Clears the list of recently opened files when you exit Windows", "Borra la lista de archivos abiertos recientemente al salir de Windows"},

        {"Disable Windows Copilot", "Deshabilitar Windows Copilot"},
        {"Disables Windows Copilot AI assistant", "Deshabilita el asistente de IA Windows Copilot"},

        // Nombres y descripciones de ajustes de privacidad
        {"Disable Sync Provider Notifications in File Explorer", "Deshabilitar notificaciones del proveedor de sincronización en el Explorador de archivos"},
        {"Disables file sync provider notifications in File Explorer", "Deshabilita las notificaciones del proveedor de sincronización de archivos en el Explorador de archivos"},

        {"Disable Fun Facts and Tips on Lock Screen", "Deshabilitar datos curiosos y consejos en la pantalla de bloqueo"},
        {"Disables fun facts, tips, tricks on your lock screen", "Deshabilita datos curiosos, consejos y trucos en tu pantalla de bloqueo"},

        {"Disable Suggested Content in Settings", "Deshabilitar contenido sugerido en Configuración"},
        {"Disables suggested content in the Settings app", "Deshabilita el contenido sugerido en la aplicación Configuración"},

        {"Disable Tips and Suggestions When Using Windows", "Deshabilitar consejos y sugerencias al usar Windows"},
        {"Disables tips and suggestions when using Windows", "Deshabilita consejos y sugerencias al usar Windows"},

        {"Disable 'Get the Most out of Windows' Suggestions", "Deshabilitar sugerencias 'Aprovecha al máximo Windows'"},
        {"Disables suggestions on how to get the most out of Windows and finish setting up the device", "Deshabilita sugerencias sobre cómo aprovechar al máximo Windows y terminar de configurar el dispositivo"},

        {"Disable Windows Welcome Experience", "Deshabilitar la experiencia de bienvenida de Windows"},
        {"Disables the Windows welcome experience after updates and when signing in", "Deshabilita la experiencia de bienvenida de Windows después de las actualizaciones y al iniciar sesión"},

        {"Disable Personalized Ads", "Deshabilitar anuncios personalizados"},
        {"Prevents apps from showing personalized ads by using your advertising ID", "Evita que las aplicaciones muestren anuncios personalizados usando tu ID de publicidad"},

        {"Disable Tailored Experiences", "Deshabilitar experiencias personalizadas"},
        {"Disables tailored experiences with diagnostic data", "Deshabilita experiencias personalizadas con datos de diagnóstico"},

        {"Disable Recommendations in Start Menu", "Deshabilitar recomendaciones en el menú Inicio"},
        {"Disables recommendations for tips, shortcuts, new apps, and more in Start menu", "Deshabilita recomendaciones de consejos, accesos directos, nuevas aplicaciones y más en el menú Inicio"},

        {"Disable Notification Suggestions", "Deshabilitar sugerencias de notificación"},
        {"Disables notification suggestions about unused apps", "Deshabilita sugerencias de notificación sobre aplicaciones no utilizadas"},

        {"Disable Bing Results in Windows Search", "Deshabilitar resultados de Bing en la Búsqueda de Windows"},
        {"Disables Bing results in Windows Search", "Deshabilita los resultados de Bing en la Búsqueda de Windows"},

        {"Disable Edge Desktop Search Widget", "Deshabilitar widget de búsqueda de escritorio de Edge"},
        {"Disables the Edge search widget on desktop", "Deshabilita el widget de búsqueda de Edge en el escritorio"},

        {"Disable Location Access", "Deshabilitar acceso a la ubicación"},
        {"Prevents apps from accessing your location", "Evita que las aplicaciones accedan a tu ubicación"},

        {"Disable Camera Access", "Deshabilitar acceso a la cámara"},
        {"Prevents apps from accessing your camera", "Evita que las aplicaciones accedan a tu cámara"},

        {"Disable Microphone Access", "Deshabilitar acceso al micrófono"},
        {"Prevents apps from accessing your microphone", "Evita que las aplicaciones accedan a tu micrófono"},

        {"Disable Documents Library Access", "Deshabilitar acceso a la biblioteca de Documentos"},
        {"Prevents apps from accessing your documents library", "Evita que las aplicaciones accedan a tu biblioteca de Documentos"},

        {"Disable Pictures Library Access", "Deshabilitar acceso a la biblioteca de Imágenes"},
        {"Prevents apps from accessing your pictures library", "Evita que las aplicaciones accedan a tu biblioteca de Imágenes"},

        {"Disable Videos Library Access", "Deshabilitar acceso a la biblioteca de Vídeos"},
        {"Prevents apps from accessing your videos library", "Evita que las aplicaciones accedan a tu biblioteca de Vídeos"},

        {"Disable Broad File System Access", "Deshabilitar acceso amplio al sistema de archivos"},
        {"Prevents apps from accessing the file system broadly", "Evita que las aplicaciones accedan ampliamente al sistema de archivos"},

        {"Disable Account Information Access", "Deshabilitar acceso a la información de la cuenta"},
        {"Prevents apps from accessing your name, picture, and account info", "Evita que las aplicaciones accedan a tu nombre, imagen e información de cuenta"},

        {"Disable Contacts Access", "Deshabilitar acceso a los contactos"},
        {"Prevents apps from accessing your contacts", "Evita que las aplicaciones accedan a tus contactos"},

        {"Disable Call History Access", "Deshabilitar acceso al historial de llamadas"},
        {"Prevents apps from accessing your call history", "Evita que las aplicaciones accedan a tu historial de llamadas"},

        {"Disable Messaging Access", "Deshabilitar acceso a la mensajería"},
        {"Prevents apps from accessing your messages", "Evita que las aplicaciones accedan a tus mensajes"},

        {"Disable Notification Access", "Deshabilitar acceso a las notifications"},
        {"Prevents apps from accessing your notifications", "Evita que las aplicaciones accedan a tus notificaciones"},

        {"Disable Email Access", "Deshabilitar acceso al correo electrónico"},
        {"Prevents apps from accessing your email", "Evita que las aplicaciones accedan a tu correo electrónico"},

        {"Disable Tasks Access", "Deshabilitar acceso a las tareas"},
        {"Prevents apps from accessing your user data tasks", "Evita que las aplicaciones accedan a tus tareas de datos de usuario"},

        {"Disable Diagnostics Access", "Deshabilitar acceso a diagnósticos"},
        {"Prevents apps from accessing your diagnostic information", "Evita que las aplicaciones accedan a tu información de diagnóstico"},

        {"Disable Voice Activation", "Deshabilitar activación por voz"},
        {"Disables voice activation for all apps", "Deshabilita la activación por voz para todas las aplicaciones"},

        {"Disable Calendar Access", "Deshabilitar acceso al calendario"},
        {"Prevents apps from accessing your calendar appointments", "Evita que las aplicaciones accedan a tus citas del calendario"},

        {"Disable Motion Access", "Deshabilitar acceso al movimiento"},
        {"Prevents apps from accessing motion data", "Evita que las aplicaciones accedan a los datos de movimiento"},

        {"Disable Radio Access", "Deshabilitar acceso a radios"},
        {"Prevents apps from accessing radio controls", "Evita que las aplicaciones accedan a los controles de radio"},

        {"Disable Activity Feed", "Deshabilitar fuente de actividades"},
        {"Disables the Windows activity feed", "Deshabilita la fuente de actividades de Windows"},

        {"Disable Notification Center", "Deshabilitar Centro de actividades"},
        {"Disables the Windows notification center", "Deshabilita el centro de actividades de Windows"},

        {"Disable Xbox Screen Recording", "Deshabilitar grabación de pantalla de Xbox"},
        {"Disables the Xbox Game DVR feature", "Deshabilita la función Xbox Game DVR"},

        {"Disable Auto Map Downloads", "Deshabilitar descarga automática de mapas"},
        {"Prevents Windows from automatically downloading map data", "Evita que Windows descargue automáticamente datos de mapas"},

        {"Disable Lock Screen Camera", "Deshabilitar cámara en pantalla de bloqueo"},
        {"Disables the camera on the lock screen", "Deshabilita la cámara en la pantalla de bloqueo"},

        {"Disable Biometrics", "Deshabilitar datos biométricos"},
        {"Disables Windows biometric features (including Windows Hello)", "Deshabilita las características biométricas de Windows (incluido Windows Hello)"},

        // Pestaña Rendimiento
        {"Windows Tweaker - Performance Settings", "Windows Tweaker - Configuración de rendimiento"},

        // Nuevos nombres y descripciones de ajustes de rendimiento
        {"Enable Confirm File Delete Dialog", "Habilitar cuadro de diálogo de confirmación al eliminar archivo"},
        {"Shows a confirmation dialog when deleting files", "Muestra un cuadro de diálogo de confirmación al eliminar archivos"},

        {"Permanently Delete Files (Skip Recycle Bin)", "Eliminar archivos permanentemente (Omitir Papelera de reciclaje)"},
        {"Deletes files permanently without moving them to the Recycle Bin", "Elimina archivos permanentemente sin moverlos a la Papelera de reciclaje"},

        // Nombres y descripciones de ajustes de rendimiento
        {"Disable Fullscreen Optimizations", "Deshabilitar optimizaciones de pantalla completa"},
        {"Disables Windows fullscreen optimizations for better game performance", "Deshabilita las optimizaciones de pantalla completa de Windows para un mejor rendimiento en juegos"},

        {"Disable Mouse Acceleration", "Deshabilitar aceleración del mouse"},
        {"Removes mouse acceleration for more consistent cursor movement", "Elimina la aceleración del mouse para un movimiento del cursor más consistente"},

        {"Disable Game Bar", "Deshabilitar Barra de juegos"},
        {"Disables Game Bar and related features to reduce overhead", "Deshabilita la Barra de juegos y funciones relacionadas para reducir la sobrecarga"},

        {"Disable Game Mode", "Deshabilitar Modo de juego"},
        {"Turns off Windows Game Mode which can cause issues with some games", "Desactiva el Modo de juego de Windows que puede causar problemas con algunos juegos"},

        {"Activate Ultimate Performance Mode", "Activar modo de Máximo rendimiento"},
        {"Activates the hidden Ultimate Performance power plan for maximum performance", "Activa el plan de energía oculto Máximo rendimiento para obtener el máximo rendimiento"},

        {"Disable Hardware Accelerated GPU Scheduling", "Deshabilitar programación de GPU acelerada por hardware"},
        {"Disables HAGS which can cause issues with some systems", "Deshabilita HAGS, que puede causar problemas con algunos sistemas"},

        {"Limit Windows Defender Usage", "Limitar uso de Windows Defender"},
        {"Limits Windows Defender CPU usage for better performance", "Limita el uso de CPU de Windows Defender para un mejor rendimiento"},

        {"Disable Core Isolation", "Deshabilitar aislamiento del núcleo"},
        {"Disables memory integrity for better performance (reduces security)", "Deshabilita la integridad de memoria para un mejor rendimiento (reduce la seguridad)"},

        {"Disable Prefetch", "Deshabilitar Prefetch"},
        {"Disables Windows Prefetch service to free up resources", "Deshabilita el servicio Prefetch de Windows para liberar recursos"},

        {"Disable Storage Sense", "Deshabilitar Sensor de almacenamiento"},
        {"Disables automatic disk cleanup to prevent background disk activity", "Deshabilita la limpieza automática de disco para prevenir actividad de disco en segundo plano"},

        {"Disable Windows Search", "Deshabilitar Búsqueda de Windows"},
        {"Disables Windows Search indexing service to free up system resources", "Deshabilita el servicio de indexación de Búsqueda de Windows para liberar recursos del sistema"},

        {"Disable Hibernation", "Deshabilitar hibernación"},
        {"Disables system hibernation to free up disk space and resources", "Deshabilita la hibernación del sistema para liberar espacio en disco y recursos"},

        // Pestaña Apariencia
        {"Windows Tweaker - Appearance Settings", "Windows Tweaker - Configuración de apariencia"},
        {"Appearance Changes Notice", "Se debe reiniciar el Explorador para aplicar los cambios"},
        {"No appearance changes requiring restart", "No hay cambios de apariencia que requieran reinicio"},
        {"Restart Explorer", "Reiniciar Explorador"},

        // Nuevos nombres y descripciones de ajustes de apariencia
        {"Hide Personalized Web Recommendations", "Ocultar recomendaciones web personalizadas"},
        {"Removes personalized website recommendations from the Start menu", "Elimina las recomendaciones de sitios web personalizados del menú Inicio"},

        {"Hide Recommended Section in Start Menu", "Ocultar sección Recomendado en el menú Inicio"},
        {"Completely removes the Recommended section from the Start menu", "Elimina completamente la sección Recomendado del menú Inicio"},

        {"Hide Clock in System Tray", "Ocultar reloj en la bandeja del sistema"},
        {"Hides the system clock from the taskbar notification area", "Oculta el reloj del sistema del área de notificación de la barra de tareas"},

        {"Hide Meet Now Icon", "Ocultar icono Reunirse ahora"},
        {"Removes the Meet Now (instant meeting) icon from the taskbar", "Elimina el icono Reunirse ahora (Meet Now) de la barra de tareas"},

        {"Disable All Balloon Notifications", "Deshabilitar todas las notificaciones de globo"},
        {"Turns off all balloon notifications from the system tray", "Desactiva todas las notificaciones de globo de la bandeja del sistema"},

        {"Hide Details Pane in File Explorer", "Ocultar panel de detalles en el Explorador de archivos"},
        {"Hides the details pane in File Explorer that shows file properties", "Oculta el panel de detalles en el Explorador de archivos que muestra las propiedades del archivo"},

        // Nombres y descripciones de ajustes de apariencia
        {"Disable Bing Search in Start Menu", "Deshabilitar búsqueda de Bing en el menú Inicio"},
        {"Controls whether the search box in the Windows Start menu performs Bing web searches", "Controla si el cuadro de búsqueda en el menú Inicio de Windows realiza búsquedas web de Bing"},

        {"Center Taskbar Icons", "Centrar iconos de la barra de tareas"},
        {"Controls whether taskbar icons are displayed centered or left-aligned", "Controla si los iconos de la barra de tareas se muestran centrados o alineados a la izquierda"},

        {"Enable Dark Mode", "Habilitar modo oscuro"},
        {"Controls whether Windows uses dark theme. Applies to apps and system interface", "Controla si Windows usa el tema oscuro. Se aplica a aplicaciones y a la interfaz del sistema"},

        {"Show Detailed BSoD", "Mostrar BSoD detallado"}, // BSoD = Pantalla Azul de la Muerte
        {"Controls whether detailed technical information is displayed on blue screen errors", "Controla si se muestra información técnica detallada en los errores de pantalla azul"},

        {"Enable Mouse Acceleration", "Habilitar aceleración del mouse"},
        {"When enabled, cursor movement is affected by the speed of your physical mouse movements", "Cuando está habilitado, el movimiento del cursor se ve afectado por la velocidad de los movimientos físicos del mouse"},

        {"Enable NumLock on Startup", "Habilitar Bloq Num al inicio"},
        {"Controls the state of the NumLock key when your computer starts", "Controla el estado de la tecla Bloq Num cuando se inicia el equipo"},

        {"Show Search Button in Taskbar", "Mostrar botón de Búsqueda en la barra de tareas"},
        {"When enabled, the search button is displayed in the taskbar", "Cuando está habilitado, el botón de búsqueda se muestra en la barra de tareas"},

        {"Show File Extensions", "Mostrar extensiones de archivo"},
        {"When enabled, file extensions (.txt, .jpg, etc.) are made visible", "Cuando está habilitado, las extensiones de archivo (.txt, .jpg, etc.) se hacen visibles"},

        {"Show Hidden Files", "Mostrar archivos ocultos"},
        {"When enabled, hidden files are displayed", "Cuando está habilitado, se muestran los archivos ocultos"},

        {"Enable Snap Assist Flyout", "Habilitar menú flotante del Asistente de acoplamiento"},
        {"When enabled, helper flyout is displayed when hovering screen corners or during window snapping", "Cuando está habilitado, se muestra un menú flotante de ayuda al pasar el cursor por las esquinas de la pantalla o durante el acoplamiento de ventanas"},

        {"Enable Snap Assist Suggestion", "Habilitar sugerencia del Asistente de acoplamiento"},
        {"When enabled, suggestions for other apps to fill remaining areas are shown during window snapping", "Cuando está habilitado, se muestran sugerencias de otras aplicaciones para llenar las áreas restantes durante el acoplamiento de ventanas"},

        {"Enable Snap Window", "Habilitar Acoplar ventanas"},
        {"When enabled, you can snap windows by dragging them to the edges of the screen", "Cuando está habilitado, puedes acoplar ventanas arrastrándolas a los bordes de la pantalla"},

        {"Enable Sticky Keys", "Habilitar Teclas especiales"},
        {"When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries", "Cuando está habilitado, se activa la función Teclas especiales - Teclas especiales es una característica de accesibilidad que ayuda a los usuarios con discapacidades físicas o ayuda a los usuarios a reducir las lesiones por esfuerzo repetitivo"},

        {"Show Task View Button in Taskbar", "Mostrar botón Vista de tareas en la barra de tareas"},
        {"When enabled, the Task View button is displayed in the taskbar", "Cuando está habilitado, el botón Vista de tareas se muestra en la barra de tareas"},

        {"Show Verbose Messages During Logon", "Mostrar mensajes detallados durante el inicio de sesión"},
        {"Shows detailed messages during login process for troubleshooting and diagnostics", "Muestra mensajes detallados durante el proceso de inicio de sesión para solución de problemas y diagnósticos"},

        {"Show Widgets Button in Taskbar", "Mostrar botón de Widgets en la barra de tareas"},
        {"When enabled, the Widgets button is displayed in the taskbar", "Cuando está habilitado, el botón de Widgets se muestra en la barra de tareas"},

        {"Enable Classic Right-Click Menu", "Habilitar menú contextual clásico"},
        {"Shows old (compact) context menu when right-clicking in file explorer on Windows 11", "Muestra el menú contextual antiguo (compacto) al hacer clic derecho en el explorador de archivos en Windows 11"},

        {"Remove Gallery from Navigation Pane", "Quitar Galería del panel de navegación"},
        {"Removes or adds the Gallery item from the navigation pane on the left side of File Explorer", "Quita o agrega el elemento Galería del panel de navegación en el lado izquierdo del Explorador de archivos"},

        {"Restarts Windows Explorer to apply changes", "Reinicia el Explorador de Windows para aplicar los cambios"},

        // Pestaña Seguridad
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Configuración de seguridad"},

        // Nombres y descripciones de ajustes de seguridad (Usando claves inglesas traducidas)
        {"Windows Defender'ı Etkinleştir", "Habilitar Windows Defender"},
        {"Windows Defender antivirüs servisi", "Servicio antivirus de Windows Defender"},

        {"Gerçek Zamanlı Korumayı Etkinleştir", "Habilitar protección en tiempo real"},
        {"Windows Defender'ın gerçek zamanlı koruma özelliği", "Característica de protección en tiempo real de Windows Defender"},

        {"SmartScreen'i Etkinleştir", "Habilitar SmartScreen"},
        {"Microsoft SmartScreen filtreleme özelliği", "Característica de filtrado de Microsoft SmartScreen"},

        {"Windows Güvenlik Duvarını Etkinleştir", "Habilitar Firewall de Windows"},
        {"Windows Güvenlik Duvarı servisi", "Servicio de Firewall de Windows"},

        {"UAC'yi Etkinleştir", "Habilitar UAC"},
        {"Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar", "Control de cuentas de usuario (UAC) - requiere confirmación del usuario para acciones que requieren privilegios de administrador"},

        {"UAC Seviyesini Yükselt", "Elevar nivel de UAC"},
        {"UAC seviyesini yüksek ayara getirir", "Establece el nivel de UAC en la configuración alta"},

        {"Güvenli Masaüstünde UAC'yi Etkinleştir", "Habilitar UAC en escritorio seguro"},
        {"UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir", "Muestra los cuadros de diálogo de UAC en un escritorio seguro inaccesible para malware"},

        {"Son Kullanıcı Adını Gizle", "Ocultar último nombre de usuario"},
        {"Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez", "No muestra el nombre del último usuario que inició sesión en la pantalla de inicio de sesión de Windows"},

        {"SMB1 Protokolünü Devre Dışı Bırak", "Deshabilitar protocolo SMB1"},
        {"Güvenlik açığı bulunan eski SMB1 protokolünü kapatır", "Desactiva el protocolo SMB1 heredado y vulnerable"},

        {"LLMNR Protokolünü Devre Dışı Bırak", "Deshabilitar protocolo LLMNR"},
        {"Link-Local Multicast Name Resolution protokolünü devre dışı bırakır", "Deshabilita el protocolo Link-Local Multicast Name Resolution"},

        {"NBT-NS'yi Devre Dışı Bırak", "Deshabilitar NBT-NS"},
        {"NetBIOS Name Service protokolünü devre dışı bırakır", "Deshabilita el protocolo NetBIOS Name Service"},

        {"Uzak Masaüstü Güvenlik Seviyesini Yükselt", "Elevar nivel de seguridad de Escritorio remoto"},
        {"Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar", "Establece el nivel de seguridad del Protocolo de Escritorio remoto (RDP) en alto"},

        {"RDP için NLA Kimlik Doğrulamasını Etkinleştir", "Habilitar autenticación NLA para RDP"},
        {"RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir", "Requiere Autenticación a nivel de red (NLA) para RDP"},

        {"RDP Şifreleme Seviyesini Yükselt", "Elevar nivel de cifrado RDP"},
        {"RDP için şifreleme seviyesini yüksek olarak ayarlar", "Establece el nivel de cifrado para RDP en alto"},

        {"AutoRun'u Devre Dışı Bırak", "Deshabilitar AutoRun"},
        {"Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır", "Deshabilita la función AutoRun en medios extraíbles"},

        {"USB Depolamayı Etkinleştir", "Habilitar almacenamiento USB"},
        {"USB depolama cihazlarını etkinleştirir veya devre dışı bırakır", "Habilita o deshabilita dispositivos de almacenamiento USB"},

        {"PowerShell Yürütme İlkesini Güvenli Yap", "Asegurar política de ejecución de PowerShell"},
        {"PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar", "Establece la política de ejecución para scripts de PowerShell en RemoteSigned"},

        {"PowerShell Komut Kaydetmeyi Etkinleştir", "Habilitar registro de comandos de PowerShell"},
        {"PowerShell komut blokları için günlük kaydını etkinleştirir", "Habilita el registro para bloques de comandos de PowerShell"},

        {"Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir", "Habilitar seguridad de Host de script"},
        {"Windows Script Host güvenliğini etkinleştirir", "Habilita la seguridad de Windows Script Host"},

        {"Windows Update'i Etkinleştir", "Habilitar Windows Update"},
        {"Windows Update servisini etkinleştirir", "Habilita el servicio Windows Update"},

        {"Otomatik Güncellemeleri Etkinleştir", "Habilitar actualizaciones automáticas"},
        {"Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar", "Permite que Windows descargue e instale actualizaciones automáticamente"},

        {"WPAD Protokolünü Devre Dışı Bırak", "Deshabilitar protocolo WPAD"},
        {"Web Proxy Auto-Discovery protokolünü devre dışı bırakır", "Deshabilita el protocolo Web Proxy Auto-Discovery"},

        {"WinRM Şifresiz Trafiği Devre Dışı Bırak", "Deshabilitar tráfico WinRM no cifrado"},
        {"Windows Remote Management için şifresiz trafiği engeller", "Bloquea el tráfico no cifrado para Windows Remote Management"},

        // Pestaña Paquetes AppX
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - Paquetes AppX"},
        {"Remove Selected Apps", "Quitar aplicaciones seleccionadas"},
        {"Select All", "Seleccionar todo"},
        {"Deselect All", "Deseleccionar todo"},
        {"Search apps", "Buscar aplicaciones"},
        {"Removing apps...", "Quitando aplicaciones..."},
        {"Successfully removed", "Quitado correctamente"},
        {"application(s)", "aplicación(es)"},
        {"No apps selected", "No hay aplicaciones seleccionadas"},
        {"System Apps", "Aplicaciones del sistema"},
        {"Warning: System apps are essential for Windows", "Advertencia: Las aplicaciones del sistema son esenciales para Windows"},
        {"Removing", "Quitando"},

        // Pestaña Configuración
        {"Windows Tweaker - Settings", "Windows Tweaker - Configuración"},

        // Pestaña Acerca de
        {"Windows Tweaker - About", "Windows Tweaker - Acerca de"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "Una herramienta completa de optimización y ajuste de Windows 11"},
        {"Developer", "Desarrollador"},
        {"Version", "Versión"},
        {"License", "Licencia"},

        // Diálogo (No hay elementos específicos listados)

        // Interruptor (Toggle)
        {"ToggleOn", "Activado"}, // Cambiado de "Açık" / "On" / "Activé" / "Ein"
        {"ToggleOff", "Desactivado"} // Cambiado de "Kapalı" / "Off" / "Désactivé" / "Aus"
    };
}