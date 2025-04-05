#pragma once
#include <string>
#include <map>

// Função renomeada para refletir que agora retorna as traduções em Português (Brasil)
inline std::map<std::string, std::string> GetPortugueseBRTranslations() {
    return {
        // Global
        {"Language", "Idioma"},
        {"English", "Inglês"},
        {"Turkish", "Turco"},
        {"German", "Alemão"},
        {"French", "Francês"},
        {"Spanish", "Espanhol"},
        {"Change Language", "Mudar idioma"},
        {"Select Language", "Selecionar idioma"},

        // Abas (Tabs)
        {"Privacy", "Privacidade"},
        {"Performance", "Desempenho"},
        {"Appearance", "Aparência"},
        {"Security", "Segurança"},
        {"Settings", "Configurações"},
        {"About", "Sobre"},
        {"AppX Packages", "Pacotes AppX"},

        // Aba Privacidade
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Configurações de Privacidade"},
        {"Enable All", "Habilitar Tudo"},
        {"Disable All", "Desabilitar Tudo"},

        // Novos nomes e dicas de ferramentas de ajustes de privacidade
        {"Clear Recent Files on Exit", "Limpar arquivos recentes ao sair"},
        {"Clears the list of recently opened files when you exit Windows", "Limpa a lista de arquivos abertos recentemente ao sair do Windows"},

        {"Disable Windows Copilot", "Desabilitar Windows Copilot"},
        {"Disables Windows Copilot AI assistant", "Desabilita o assistente de IA Windows Copilot"},

        // Nomes e dicas de ferramentas de ajustes de privacidade
        {"Disable Sync Provider Notifications in File Explorer", "Desabilitar notificações do provedor de sincronização no Explorador de Arquivos"},
        {"Disables file sync provider notifications in File Explorer", "Desabilita as notificações do provedor de sincronização de arquivos no Explorador de Arquivos"},

        {"Disable Fun Facts and Tips on Lock Screen", "Desabilitar fatos divertidos e dicas na tela de bloqueio"},
        {"Disables fun facts, tips, tricks on your lock screen", "Desabilita fatos divertidos, dicas e truques na sua tela de bloqueio"},

        {"Disable Suggested Content in Settings", "Desabilitar conteúdo sugerido nas Configurações"},
        {"Disables suggested content in the Settings app", "Desabilita o conteúdo sugerido no aplicativo Configurações"},

        {"Disable Tips and Suggestions When Using Windows", "Desabilitar dicas e sugestões ao usar o Windows"},
        {"Disables tips and suggestions when using Windows", "Desabilita dicas e sugestões ao usar o Windows"},

        {"Disable 'Get the Most out of Windows' Suggestions", "Desabilitar sugestões 'Aproveite ao máximo o Windows'"},
        {"Disables suggestions on how to get the most out of Windows and finish setting up the device", "Desabilita sugestões sobre como aproveitar ao máximo o Windows e concluir a configuração do dispositivo"},

        {"Disable Windows Welcome Experience", "Desabilitar Experiência de Boas-vindas do Windows"},
        {"Disables the Windows welcome experience after updates and when signing in", "Desabilita a experiência de boas-vindas do Windows após atualizações e ao entrar"},

        {"Disable Personalized Ads", "Desabilitar anúncios personalizados"},
        {"Prevents apps from showing personalized ads by using your advertising ID", "Impede que aplicativos mostrem anúncios personalizados usando seu ID de publicidade"},

        {"Disable Tailored Experiences", "Desabilitar experiências personalizadas"},
        {"Disables tailored experiences with diagnostic data", "Desabilita experiências personalizadas com dados de diagnóstico"},

        {"Disable Recommendations in Start Menu", "Desabilitar recomendações no Menu Iniciar"},
        {"Disables recommendations for tips, shortcuts, new apps, and more in Start menu", "Desabilita recomendações de dicas, atalhos, novos aplicativos e mais no menu Iniciar"},

        {"Disable Notification Suggestions", "Desabilitar sugestões de notificação"},
        {"Disables notification suggestions about unused apps", "Desabilita sugestões de notificação sobre aplicativos não utilizados"},

        {"Disable Bing Results in Windows Search", "Desabilitar resultados do Bing na Pesquisa do Windows"},
        {"Disables Bing results in Windows Search", "Desabilita os resultados do Bing na Pesquisa do Windows"},

        {"Disable Edge Desktop Search Widget", "Desabilitar widget de pesquisa da área de trabalho do Edge"},
        {"Disables the Edge search widget on desktop", "Desabilita o widget de pesquisa do Edge na área de trabalho"},

        {"Disable Location Access", "Desabilitar acesso à localização"},
        {"Prevents apps from accessing your location", "Impede que aplicativos acessem sua localização"},

        {"Disable Camera Access", "Desabilitar acesso à câmera"},
        {"Prevents apps from accessing your camera", "Impede que aplicativos acessem sua câmera"},

        {"Disable Microphone Access", "Desabilitar acesso ao microfone"},
        {"Prevents apps from accessing your microphone", "Impede que aplicativos acessem seu microfone"},

        {"Disable Documents Library Access", "Desabilitar acesso à biblioteca Documentos"},
        {"Prevents apps from accessing your documents library", "Impede que aplicativos acessem sua biblioteca de Documentos"},

        {"Disable Pictures Library Access", "Desabilitar acesso à biblioteca Imagens"},
        {"Prevents apps from accessing your pictures library", "Impede que aplicativos acessem sua biblioteca de Imagens"},

        {"Disable Videos Library Access", "Desabilitar acesso à biblioteca Vídeos"},
        {"Prevents apps from accessing your videos library", "Impede que aplicativos acessem sua biblioteca de Vídeos"},

        {"Disable Broad File System Access", "Desabilitar acesso amplo ao sistema de arquivos"},
        {"Prevents apps from accessing the file system broadly", "Impede que aplicativos acessem amplamente o sistema de arquivos"},

        {"Disable Account Information Access", "Desabilitar acesso às informações da conta"},
        {"Prevents apps from accessing your name, picture, and account info", "Impede que aplicativos acessem seu nome, foto e informações da conta"},

        {"Disable Contacts Access", "Desabilitar acesso aos contatos"},
        {"Prevents apps from accessing your contacts", "Impede que aplicativos acessem seus contatos"},

        {"Disable Call History Access", "Desabilitar acesso ao histórico de chamadas"},
        {"Prevents apps from accessing your call history", "Impede que aplicativos acessem seu histórico de chamadas"},

        {"Disable Messaging Access", "Desabilitar acesso a mensagens"},
        {"Prevents apps from accessing your messages", "Impede que aplicativos acessem suas mensagens"},

        {"Disable Notification Access", "Desabilitar acesso a notificações"},
        {"Prevents apps from accessing your notifications", "Impede que aplicativos acessem suas notificações"},

        {"Disable Email Access", "Desabilitar acesso ao e-mail"},
        {"Prevents apps from accessing your email", "Impede que aplicativos acessem seu e-mail"},

        {"Disable Tasks Access", "Desabilitar acesso a tarefas"},
        {"Prevents apps from accessing your user data tasks", "Impede que aplicativos acessem suas tarefas de dados do usuário"},

        {"Disable Diagnostics Access", "Desabilitar acesso a diagnósticos"},
        {"Prevents apps from accessing your diagnostic information", "Impede que aplicativos acessem suas informações de diagnóstico"},

        {"Disable Voice Activation", "Desabilitar ativação por voz"},
        {"Disables voice activation for all apps", "Desabilita a ativação por voz para todos os aplicativos"},

        {"Disable Calendar Access", "Desabilitar acesso ao calendário"},
        {"Prevents apps from accessing your calendar appointments", "Impede que aplicativos acessem seus compromissos do calendário"},

        {"Disable Motion Access", "Desabilitar acesso a movimento"},
        {"Prevents apps from accessing motion data", "Impede que aplicativos acessem dados de movimento"},

        {"Disable Radio Access", "Desabilitar acesso a rádio"},
        {"Prevents apps from accessing radio controls", "Impede que aplicativos acessem controles de rádio"},

        {"Disable Activity Feed", "Desabilitar feed de atividades"},
        {"Disables the Windows activity feed", "Desabilita o feed de atividades do Windows"},

        {"Disable Notification Center", "Desabilitar Central de Notificações"},
        {"Disables the Windows notification center", "Desabilita a central de notificações do Windows"},

        {"Disable Xbox Screen Recording", "Desabilitar gravação de tela do Xbox"},
        {"Disables the Xbox Game DVR feature", "Desabilita o recurso Xbox Game DVR"},

        {"Disable Auto Map Downloads", "Desabilitar download automático de mapas"},
        {"Prevents Windows from automatically downloading map data", "Impede que o Windows baixe automaticamente dados de mapas"},

        {"Disable Lock Screen Camera", "Desabilitar câmera da tela de bloqueio"},
        {"Disables the camera on the lock screen", "Desabilita a câmera na tela de bloqueio"},

        {"Disable Biometrics", "Desabilitar biometria"},
        {"Disables Windows biometric features (including Windows Hello)", "Desabilita recursos biométricos do Windows (incluindo o Windows Hello)"},

        // Aba Desempenho
        {"Windows Tweaker - Performance Settings", "Windows Tweaker - Configurações de Desempenho"},

        // Novos nomes e dicas de ferramentas de ajustes de desempenho
        {"Enable Confirm File Delete Dialog", "Habilitar diálogo de confirmação ao excluir arquivo"},
        {"Shows a confirmation dialog when deleting files", "Mostra um diálogo de confirmação ao excluir arquivos"},

        {"Permanently Delete Files (Skip Recycle Bin)", "Excluir arquivos permanentemente (Ignorar Lixeira)"},
        {"Deletes files permanently without moving them to the Recycle Bin", "Exclui arquivos permanentemente sem movê-los para a Lixeira"},

        // Nomes e dicas de ferramentas de ajustes de desempenho
        {"Disable Fullscreen Optimizations", "Desabilitar otimizações de tela inteira"},
        {"Disables Windows fullscreen optimizations for better game performance", "Desabilita as otimizações de tela inteira do Windows para melhor desempenho em jogos"},

        {"Disable Mouse Acceleration", "Desabilitar aceleração do mouse"},
        {"Removes mouse acceleration for more consistent cursor movement", "Remove a aceleração do mouse para um movimento do cursor mais consistente"},

        {"Disable Game Bar", "Desabilitar Barra de Jogo"},
        {"Disables Game Bar and related features to reduce overhead", "Desabilita a Barra de Jogo e recursos relacionados para reduzir a sobrecarga"},

        {"Disable Game Mode", "Desabilitar Modo de Jogo"},
        {"Turns off Windows Game Mode which can cause issues with some games", "Desliga o Modo de Jogo do Windows, que pode causar problemas com alguns jogos"},

        {"Activate Ultimate Performance Mode", "Ativar modo Desempenho Máximo"},
        {"Activates the hidden Ultimate Performance power plan for maximum performance", "Ativa o plano de energia oculto Desempenho Máximo para desempenho máximo"},

        {"Disable Hardware Accelerated GPU Scheduling", "Desabilitar agendamento de GPU acelerado por hardware"},
        {"Disables HAGS which can cause issues with some systems", "Desabilita o HAGS, que pode causar problemas em alguns sistemas"},

        {"Limit Windows Defender Usage", "Limitar uso do Windows Defender"},
        {"Limits Windows Defender CPU usage for better performance", "Limita o uso da CPU pelo Windows Defender para melhor desempenho"},

        {"Disable Core Isolation", "Desabilitar Isolamento de Núcleo"},
        {"Disables memory integrity for better performance (reduces security)", "Desabilita a integridade da memória para melhor desempenho (reduz a segurança)"},

        {"Disable Prefetch", "Desabilitar Prefetch"},
        {"Disables Windows Prefetch service to free up resources", "Desabilita o serviço Prefetch do Windows para liberar recursos"},

        {"Disable Storage Sense", "Desabilitar Sensor de Armazenamento"},
        {"Disables automatic disk cleanup to prevent background disk activity", "Desabilita a limpeza automática de disco para evitar atividade de disco em segundo plano"},

        {"Disable Windows Search", "Desabilitar Pesquisa do Windows"},
        {"Disables Windows Search indexing service to free up system resources", "Desabilita o serviço de indexação da Pesquisa do Windows para liberar recursos do sistema"},

        {"Disable Hibernation", "Desabilitar Hibernação"},
        {"Disables system hibernation to free up disk space and resources", "Desabilita a hibernação do sistema para liberar espaço em disco e recursos"},

        // Aba Aparência
        {"Windows Tweaker - Appearance Settings", "Windows Tweaker - Configurações de Aparência"},
        {"Appearance Changes Notice", "O Explorer deve ser reiniciado para aplicar as alterações"},
        {"No appearance changes requiring restart", "Nenhuma alteração de aparência requer reinicialização"},
        {"Restart Explorer", "Reiniciar Explorer"},

        // Novos nomes e dicas de ferramentas de ajustes de aparência
        {"Hide Personalized Web Recommendations", "Ocultar recomendações da Web personalizadas"},
        {"Removes personalized website recommendations from the Start menu", "Remove recomendações de sites personalizadas do menu Iniciar"},

        {"Hide Recommended Section in Start Menu", "Ocultar seção Recomendado no Menu Iniciar"},
        {"Completely removes the Recommended section from the Start menu", "Remove completamente a seção Recomendado do menu Iniciar"},

        {"Hide Clock in System Tray", "Ocultar relógio na bandeja do sistema"},
        {"Hides the system clock from the taskbar notification area", "Oculta o relógio do sistema da área de notificação da barra de tarefas"},

        {"Hide Meet Now Icon", "Ocultar ícone Reunir Agora"},
        {"Removes the Meet Now (instant meeting) icon from the taskbar", "Remove o ícone Reunir Agora (Meet Now) da barra de tarefas"},

        {"Disable All Balloon Notifications", "Desabilitar todas as notificações de balão"},
        {"Turns off all balloon notifications from the system tray", "Desliga todas as notificações de balão da bandeja do sistema"},

        {"Hide Details Pane in File Explorer", "Ocultar painel de Detalhes no Explorador de Arquivos"},
        {"Hides the details pane in File Explorer that shows file properties", "Oculta o painel de detalhes no Explorador de Arquivos que mostra as propriedades do arquivo"},

        // Nomes e dicas de ferramentas de ajustes de aparência
        {"Disable Bing Search in Start Menu", "Desabilitar pesquisa do Bing no Menu Iniciar"},
        {"Controls whether the search box in the Windows Start menu performs Bing web searches", "Controla se a caixa de pesquisa no menu Iniciar do Windows realiza pesquisas na web do Bing"},

        {"Center Taskbar Icons", "Centralizar ícones da barra de tarefas"},
        {"Controls whether taskbar icons are displayed centered or left-aligned", "Controla se os ícones da barra de tarefas são exibidos centralizados ou alinhados à esquerda"},

        {"Enable Dark Mode", "Habilitar modo escuro"},
        {"Controls whether Windows uses dark theme. Applies to apps and system interface", "Controla se o Windows usa o tema escuro. Aplica-se a aplicativos e interface do sistema"},

        {"Show Detailed BSoD", "Mostrar BSoD detalhado"}, // BSoD = Tela Azul da Morte
        {"Controls whether detailed technical information is displayed on blue screen errors", "Controla se informações técnicas detalhadas são exibidas em erros de tela azul"},

        {"Enable Mouse Acceleration", "Habilitar aceleração do mouse"},
        {"When enabled, cursor movement is affected by the speed of your physical mouse movements", "Quando habilitado, o movimento do cursor é afetado pela velocidade dos movimentos físicos do mouse"},

        {"Enable NumLock on Startup", "Habilitar NumLock na inicialização"},
        {"Controls the state of the NumLock key when your computer starts", "Controla o estado da tecla NumLock quando o computador é iniciado"},

        {"Show Search Button in Taskbar", "Mostrar botão de Pesquisa na barra de tarefas"},
        {"When enabled, the search button is displayed in the taskbar", "Quando habilitado, o botão de pesquisa é exibido na barra de tarefas"},

        {"Show File Extensions", "Mostrar extensões de arquivo"},
        {"When enabled, file extensions (.txt, .jpg, etc.) are made visible", "Quando habilitado, as extensões de arquivo (.txt, .jpg, etc.) ficam visíveis"},

        {"Show Hidden Files", "Mostrar arquivos ocultos"},
        {"When enabled, hidden files are displayed", "Quando habilitado, os arquivos ocultos são exibidos"},

        {"Enable Snap Assist Flyout", "Habilitar menu flutuante do Assistente de Ajuste"},
        {"When enabled, helper flyout is displayed when hovering screen corners or during window snapping", "Quando habilitado, um menu flutuante auxiliar é exibido ao passar o mouse nos cantos da tela ou durante o ajuste de janelas"},

        {"Enable Snap Assist Suggestion", "Habilitar sugestão do Assistente de Ajuste"},
        {"When enabled, suggestions for other apps to fill remaining areas are shown during window snapping", "Quando habilitado, sugestões de outros aplicativos para preencher áreas restantes são mostradas durante o ajuste de janelas"},

        {"Enable Snap Window", "Habilitar Ajustar Janelas"},
        {"When enabled, you can snap windows by dragging them to the edges of the screen", "Quando habilitado, você pode ajustar janelas arrastando-as para as bordas da tela"},

        {"Enable Sticky Keys", "Habilitar Teclas de Aderência"},
        {"When enabled, Sticky Keys feature is activated - Sticky Keys is an accessibility feature that helps users with physical disabilities or helps users reduce repetitive strain injuries", "Quando habilitado, o recurso Teclas de Aderência é ativado - Teclas de Aderência é um recurso de acessibilidade que ajuda usuários com deficiências físicas ou ajuda a reduzir lesões por esforço repetitivo"},

        {"Show Task View Button in Taskbar", "Mostrar botão Visão de Tarefas na barra de tarefas"},
        {"When enabled, the Task View button is displayed in the taskbar", "Quando habilitado, o botão Visão de Tarefas é exibido na barra de tarefas"},

        {"Show Verbose Messages During Logon", "Mostrar mensagens detalhadas durante o logon"},
        {"Shows detailed messages during login process for troubleshooting and diagnostics", "Mostra mensagens detalhadas durante o processo de logon para solução de problemas e diagnósticos"},

        {"Show Widgets Button in Taskbar", "Mostrar botão Widgets na barra de tarefas"},
        {"When enabled, the Widgets button is displayed in the taskbar", "Quando habilitado, o botão Widgets é exibido na barra de tarefas"},

        {"Enable Classic Right-Click Menu", "Habilitar Menu Clássico de Clique Direito"},
        {"Shows old (compact) context menu when right-clicking in file explorer on Windows 11", "Mostra o menu de contexto antigo (compacto) ao clicar com o botão direito no explorador de arquivos no Windows 11"},

        {"Remove Gallery from Navigation Pane", "Remover Galeria do Painel de Navegação"},
        {"Removes or adds the Gallery item from the navigation pane on the left side of File Explorer", "Remove ou adiciona o item Galeria do painel de navegação no lado esquerdo do Explorador de Arquivos"},

        {"Restarts Windows Explorer to apply changes", "Reinicia o Explorador do Windows para aplicar as alterações"},

        // Aba Segurança
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Configurações de Segurança"},

        // Nomes e dicas de ferramentas de ajustes de segurança (Usando chaves inglesas traduzidas)
        {"Windows Defender'ı Etkinleştir", "Habilitar Windows Defender"},
        {"Windows Defender antivirüs servisi", "Serviço antivírus Windows Defender"},

        {"Gerçek Zamanlı Korumayı Etkinleştir", "Habilitar proteção em tempo real"},
        {"Windows Defender'ın gerçek zamanlı koruma özelliği", "Recurso de proteção em tempo real do Windows Defender"},

        {"SmartScreen'i Etkinleştir", "Habilitar SmartScreen"},
        {"Microsoft SmartScreen filtreleme özelliği", "Recurso de filtragem Microsoft SmartScreen"},

        {"Windows Güvenlik Duvarını Etkinleştir", "Habilitar Firewall do Windows"},
        {"Windows Güvenlik Duvarı servisi", "Serviço do Firewall do Windows"},

        {"UAC'yi Etkinleştir", "Habilitar UAC"},
        {"Kullanıcı Hesabı Denetimi (UAC) - kullanıcının yönetici izni gerektiren eylemleri onaylamasını zorunlu kılar", "Controle de Conta de Usuário (UAC) - exige confirmação do usuário para ações que requerem privilégios de administrador"},

        {"UAC Seviyesini Yükselt", "Elevar nível do UAC"},
        {"UAC seviyesini yüksek ayara getirir", "Define o nível do UAC para a configuração alta"},

        {"Güvenli Masaüstünde UAC'yi Etkinleştir", "Habilitar UAC na área de trabalho segura"},
        {"UAC iletişim kutularını, kötü amaçlı yazılımların erişemeyeceği güvenli bir masaüstünde gösterir", "Mostra diálogos do UAC em uma área de trabalho segura inacessível a malware"},

        {"Son Kullanıcı Adını Gizle", "Ocultar último nome de usuário"},
        {"Windows oturum açma ekranında son oturum açan kullanıcının adını göstermez", "Não mostra o nome do último usuário conectado na tela de logon do Windows"},

        {"SMB1 Protokolünü Devre Dışı Bırak", "Desabilitar protocolo SMB1"},
        {"Güvenlik açığı bulunan eski SMB1 protokolünü kapatır", "Desliga o protocolo SMB1 legado vulnerável"},

        {"LLMNR Protokolünü Devre Dışı Bırak", "Desabilitar protocolo LLMNR"},
        {"Link-Local Multicast Name Resolution protokolünü devre dışı bırakır", "Desabilita o protocolo Link-Local Multicast Name Resolution"},

        {"NBT-NS'yi Devre Dışı Bırak", "Desabilitar NBT-NS"},
        {"NetBIOS Name Service protokolünü devre dışı bırakır", "Desabilita o protocolo NetBIOS Name Service"},

        {"Uzak Masaüstü Güvenlik Seviyesini Yükselt", "Elevar nível de segurança da Área de Trabalho Remota"},
        {"Uzak Masaüstü Protokolü (RDP) güvenlik seviyesini yüksek olarak ayarlar", "Define o nível de segurança do Protocolo de Área de Trabalho Remota (RDP) como alto"},

        {"RDP için NLA Kimlik Doğrulamasını Etkinleştir", "Habilitar autenticação NLA para RDP"},
        {"RDP için Ağ Seviyesi Kimlik Doğrulaması (NLA) gerektirir", "Requer Autenticação no Nível da Rede (NLA) para RDP"},

        {"RDP Şifreleme Seviyesini Yükselt", "Elevar nível de criptografia RDP"},
        {"RDP için şifreleme seviyesini yüksek olarak ayarlar", "Define o nível de criptografia para RDP como alto"},

        {"AutoRun'u Devre Dışı Bırak", "Desabilitar AutoRun"},
        {"Çıkarılabilir medyada AutoRun özelliğini devre dışı bırakır", "Desabilita o recurso AutoRun em mídias removíveis"},

        {"USB Depolamayı Etkinleştir", "Habilitar armazenamento USB"},
        {"USB depolama cihazlarını etkinleştirir veya devre dışı bırakır", "Habilita ou desabilita dispositivos de armazenamento USB"},

        {"PowerShell Yürütme İlkesini Güvenli Yap", "Tornar segura a política de execução do PowerShell"},
        {"PowerShell betikleri için yürütme ilkesini RemoteSigned olarak ayarlar", "Define a política de execução para scripts do PowerShell como RemoteSigned"},

        {"PowerShell Komut Kaydetmeyi Etkinleştir", "Habilitar log de comandos do PowerShell"},
        {"PowerShell komut blokları için günlük kaydını etkinleştirir", "Habilita o log para blocos de comando do PowerShell"},

        {"Komut Dosyası Ana Bilgisayar Güvenliğini Etkinleştir", "Habilitar segurança do Host de Script"},
        {"Windows Script Host güvenliğini etkinleştirir", "Habilita a segurança do Windows Script Host"},

        {"Windows Update'i Etkinleştir", "Habilitar Windows Update"},
        {"Windows Update servisini etkinleştirir", "Habilita o serviço Windows Update"},

        {"Otomatik Güncellemeleri Etkinleştir", "Habilitar atualizações automáticas"},
        {"Windows'un güncellemeleri otomatik olarak indirip yüklemesini sağlar", "Permite que o Windows baixe e instale atualizações automaticamente"},

        {"WPAD Protokolünü Devre Dışı Bırak", "Desabilitar protocolo WPAD"},
        {"Web Proxy Auto-Discovery protokolünü devre dışı bırakır", "Desabilita o protocolo Web Proxy Auto-Discovery"},

        {"WinRM Şifresiz Trafiği Devre Dışı Bırak", "Desabilitar tráfego WinRM não criptografado"},
        {"Windows Remote Management için şifresiz trafiği engeller", "Bloqueia tráfego não criptografado para o Gerenciamento Remoto do Windows"},

        // Aba Pacotes AppX
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - Pacotes AppX"},
        {"Remove Selected Apps", "Remover aplicativos selecionados"},
        {"Select All", "Selecionar Tudo"},
        {"Deselect All", "Desmarcar Tudo"},
        {"Search apps", "Pesquisar aplicativos"},
        {"Removing apps...", "Removendo aplicativos..."},
        {"Successfully removed", "Removido com sucesso"},
        {"application(s)", "aplicativo(s)"},
        {"No apps selected", "Nenhum aplicativo selecionado"},
        {"System Apps", "Aplicativos do sistema"},
        {"Warning: System apps are essential for Windows", "Aviso: Aplicativos do sistema são essenciais para o Windows"},
        {"Removing", "Removendo"},

        // Aba Configurações
        {"Windows Tweaker - Settings", "Windows Tweaker - Configurações"},

        // Aba Sobre
        {"Windows Tweaker - About", "Windows Tweaker - Sobre"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "Uma ferramenta abrangente de otimização e ajuste do Windows 11"},
        {"Developer", "Desenvolvedor"},
        {"Version", "Versão"},
        {"License", "Licença"},

        // Diálogo (Nenhum item específico listado)

        // Alternar (Toggle)
        {"ToggleOn", "Ligado"},
        {"ToggleOff", "Desligado"}
    };
}