#pragma once
#include <string>
#include <map>

inline std::map<std::string, std::string> GetPortugueseBRTranslations() {
    return {
        // Global
        {"Language", "Idioma"},
        {"English", "Inglês"},
        {"Turkish", "Turco"},
        {"German", "Alemão"},
        {"French", "Francês"},
        {"Spanish", "Espanhol"},
        {"Italian", "Italiano"},
        {"Portuguese (Brazil)", "Português (Brasil)"},
        {"Russian", "Russo"},
        {"Chinese (Simplified)", "Chinês (Simplificado)"},
        {"Change Language", "Mudar Idioma"},
        {"Select Language", "Selecionar Idioma"},
        
        // Tabs
        {"Privacy", "Privacidade"},
        {"Performance", "Desempenho"},
        {"Appearance", "Aparência"},
        {"Security", "Segurança"},
        {"Settings", "Configurações"},
        {"About", "Sobre"},
        {"AppX Packages", "Pacotes AppX"},
        
        // Privacy Tab
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Configurações de Privacidade"},
        {"Enable All", "Ativar Tudo"},
        {"Disable All", "Desativar Tudo"},
        
        // Basic Privacy Tweaks
        {"Clear Recent Files on Exit", "Limpar Arquivos Recentes ao Sair"},
        {"Disable Windows Copilot", "Desativar Windows Copilot"},
        
        // Security Tab
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Configurações de Segurança"},
        
        // AppX Packages Tab
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - Pacotes AppX"},
        {"Remove Selected Apps", "Remover Aplicativos Selecionados"},
        {"Select All", "Selecionar Tudo"},
        {"Deselect All", "Desmarcar Tudo"},
        {"Search apps", "Pesquisar aplicativos"},
        {"Removing apps...", "Removendo aplicativos..."},
        {"Successfully removed", "Removido com sucesso"},
        {"application(s)", "aplicativo(s)"},
        {"No apps selected", "Nenhum aplicativo selecionado"},
        {"System Apps", "Aplicativos do Sistema"},
        {"Warning: System apps are essential for Windows", "Aviso: Aplicativos do sistema são essenciais para o Windows"},
        {"Removing", "Removendo"},
        
        // Settings Tab
        {"Windows Tweaker - Settings", "Windows Tweaker - Configurações"},
        
        // About Tab
        {"Windows Tweaker - About", "Windows Tweaker - Sobre"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "Uma ferramenta abrangente de otimização para Windows 11"},
        {"Developer", "Desenvolvedor"},
        {"Version", "Versão"},
        {"License", "Licença"},
        
        // Toggle
        {"ToggleOn", "Ativado"},
        {"ToggleOff", "Desativado"}
    };
} 