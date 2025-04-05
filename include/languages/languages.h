#pragma once
// ÖNEMLİ: Bu dosya UTF-8 karakter kodlaması ile kaydedilmelidir!
// IMPORTANT: This file MUST be saved with UTF-8 encoding!

#include <string>
#include <map>

// Tüm dil dosyalarını dahil et
#include "english.h"
#include "turkish.h"
#include "german.h"
#include "french.h"
#include "spanish.h"
#include "italian.h"
#include "portugueseBR.h"
// Rusça ve Çince kaldırıldı
// #include "russian.h"
// #include "chineseSimplified.h"
// Gelecekte eklenecek yeni diller burada dahil edilebilir
// #include "example.h"

// Language management class
class LanguageManager {
private:
    std::map<std::string, std::string> translations;
    std::string currentLanguage;

    // Map of supported languages - language code and display name
    const std::map<std::string, std::string> supportedLanguages = {
        {"en", "English"},
        {"tr", "Turkish"},
        {"de", "German"},
        {"fr", "French"},
        {"es", "Spanish"},
        {"it", "Italian"},
        {"pt-br", "Portuguese (Brazil)"}
        // Rusça ve Çince kaldırıldı
        // {"ru", "Russian"},
        // {"zh", "Chinese (Simplified)"}
        // Gelecekte yeni diller burada eklenebilir
        // {"code", "Language Name"}
    };

public:
    LanguageManager() : currentLanguage("en") {
        // Load English by default
        translations = GetEnglishTranslations();
    }

    // Load language function
    bool LoadLanguage(const std::string& langCode) {
        currentLanguage = langCode;

        // Load the correct translation based on language code
        if (langCode == "en") {
            translations = GetEnglishTranslations();
        } else if (langCode == "tr") {
            translations = GetTurkishTranslations();
        } else if (langCode == "de") {
            translations = GetGermanTranslations();
        } else if (langCode == "fr") {
            translations = GetFrenchTranslations();
        } else if (langCode == "es") {
            translations = GetSpanishTranslations();
        } else if (langCode == "it") {
            translations = GetItalianTranslations();
        } else if (langCode == "pt-br") {
            translations = GetPortugueseBRTranslations();
        }
        // Rusça ve Çince kaldırıldı
        // else if (langCode == "ru") {
        //    translations = GetRussianTranslations();
        // } else if (langCode == "zh") {
        //    translations = GetChineseSimplifiedTranslations();
        // }
        // Gelecekte yeni diller burada eklenebilir
        // else if (langCode == "xx") {
        //     translations = GetXXTranslations();
        // }
        else {
            // Use English for unknown language codes
            translations = GetEnglishTranslations();
            currentLanguage = "en";
            return false;
        }

        return true;
    }

    // Text translation function
    std::string Translate(const std::string& key) {
        auto it = translations.find(key);
        if (it != translations.end()) {
            return it->second;
        }
        // If no translation is found, return the key itself
        return key;
    }

    // Get current language
    std::string GetCurrentLanguage() const {
        return currentLanguage;
    }

    // List supported languages
    std::map<std::string, std::string> GetAvailableLanguages() const {
        return supportedLanguages;
    }

    // Get display name from language code
    std::string GetLanguageDisplayName(const std::string& langCode) const {
        auto it = supportedLanguages.find(langCode);
        if (it != supportedLanguages.end()) {
            return it->second;
        }
        return langCode; // Return code for unknown language
    }
}; 