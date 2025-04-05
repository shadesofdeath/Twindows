#pragma once
#include <string>
#include <map>

inline std::map<std::string, std::string> GetItalianTranslations() {
    return {
        // Global
        {"Language", "Lingua"},
        {"English", "Inglese"},
        {"Turkish", "Turco"},
        {"German", "Tedesco"},
        {"French", "Francese"},
        {"Spanish", "Spagnolo"},
        {"Italian", "Italiano"},
        {"Portuguese (Brazil)", "Portoghese (Brasile)"},
        {"Russian", "Russo"},
        {"Chinese (Simplified)", "Cinese (Semplificato)"},
        {"Change Language", "Cambia Lingua"},
        {"Select Language", "Seleziona Lingua"},
        
        // Tabs
        {"Privacy", "Privacy"},
        {"Performance", "Prestazioni"},
        {"Appearance", "Aspetto"},
        {"Security", "Sicurezza"},
        {"Settings", "Impostazioni"},
        {"About", "Info"},
        {"AppX Packages", "Pacchetti AppX"},
        
        // Privacy Tab
        {"Windows Tweaker - Privacy Settings", "Windows Tweaker - Impostazioni Privacy"},
        {"Enable All", "Abilita Tutto"},
        {"Disable All", "Disabilita Tutto"},
        
        // Basic Privacy Tweaks
        {"Clear Recent Files on Exit", "Cancella File Recenti all'Uscita"},
        {"Disable Windows Copilot", "Disabilita Windows Copilot"},
        
        // Security Tab
        {"Windows Tweaker - Security Settings", "Windows Tweaker - Impostazioni di Sicurezza"},
        
        // AppX Packages Tab
        {"Windows Tweaker - AppX Packages", "Windows Tweaker - Pacchetti AppX"},
        {"Remove Selected Apps", "Rimuovi App Selezionate"},
        {"Select All", "Seleziona Tutto"},
        {"Deselect All", "Deseleziona Tutto"},
        {"Search apps", "Cerca app"},
        {"Removing apps...", "Rimozione app in corso..."},
        {"Successfully removed", "Rimosso con successo"},
        {"application(s)", "applicazione(i)"},
        {"No apps selected", "Nessuna app selezionata"},
        {"System Apps", "App di Sistema"},
        {"Warning: System apps are essential for Windows", "Attenzione: Le app di sistema sono essenziali per Windows"},
        {"Removing", "Rimozione"},
        
        // Settings Tab
        {"Windows Tweaker - Settings", "Windows Tweaker - Impostazioni"},
        
        // About Tab
        {"Windows Tweaker - About", "Windows Tweaker - Info"},
        {"A comprehensive Windows 11 optimization and tweaking tool", "Uno strumento completo per l'ottimizzazione di Windows 11"},
        {"Developer", "Sviluppatore"},
        {"Version", "Versione"},
        {"License", "Licenza"},
        
        // Toggle
        {"ToggleOn", "Attivo"},
        {"ToggleOff", "Disattivo"}
    };
} 