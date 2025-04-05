#pragma once
#include <string>
#include <Windows.h>
#include <winsvc.h> // For service management
#include <shellapi.h> // For ShellExecute
#include <winreg.h> // For registry access
#include <comdef.h> // COM tanımlamaları için
#include <Wbemidl.h> // WMI için
#pragma comment(lib, "wbemuuid.lib") // WMI kütüphanesi

namespace WindowsUtils {

    // Registry operations
    inline bool SetRegistryValueDWORD(HKEY rootKey, const std::string& subKey, const std::string& valueName, DWORD value) {
        HKEY hKey;
        // Daha yüksek izinler ekle - özellikle HKEY_LOCAL_MACHINE anahtarları için gerekli
        REGSAM access = KEY_WRITE;
        
        // 64-bit sistemlerde 32-bit uygulamalar için gerekli
        #ifdef _WIN64
            // 64-bit uygulama, normal erişim yeterli
        #else
            if (rootKey == HKEY_LOCAL_MACHINE || rootKey == HKEY_CLASSES_ROOT) {
                access |= KEY_WOW64_64KEY; // 64-bit kayıt defterine erişim
            }
        #endif
        
        LONG result = RegCreateKeyExA(rootKey, subKey.c_str(), 0, NULL, 
                                     REG_OPTION_NON_VOLATILE, access, NULL, &hKey, NULL);
        
        if (result != ERROR_SUCCESS) {
            // Admin yetkileri gerekebilir, hata kodu döndür
            return false;
        }
        
        result = RegSetValueExA(hKey, valueName.c_str(), 0, REG_DWORD, 
                               reinterpret_cast<const BYTE*>(&value), sizeof(DWORD));
        
        RegCloseKey(hKey);
        return (result == ERROR_SUCCESS);
    }
    
    inline bool SetRegistryValueString(HKEY rootKey, const std::string& subKey, const std::string& valueName, const std::string& value) {
        HKEY hKey;
        // Daha yüksek izinler ekle
        REGSAM access = KEY_WRITE;
        
        // 64-bit sistemlerde 32-bit uygulamalar için gerekli
        #ifdef _WIN64
            // 64-bit uygulama, normal erişim yeterli
        #else
            if (rootKey == HKEY_LOCAL_MACHINE || rootKey == HKEY_CLASSES_ROOT) {
                access |= KEY_WOW64_64KEY; // 64-bit kayıt defterine erişim
            }
        #endif
        
        LONG result = RegCreateKeyExA(rootKey, subKey.c_str(), 0, NULL, 
                                     REG_OPTION_NON_VOLATILE, access, NULL, &hKey, NULL);
        
        if (result != ERROR_SUCCESS) {
            // Admin yetkileri gerekebilir
            return false;
        }
        
        result = RegSetValueExA(hKey, valueName.c_str(), 0, REG_SZ, 
                               reinterpret_cast<const BYTE*>(value.c_str()), static_cast<DWORD>(value.size() + 1));
        
        RegCloseKey(hKey);
        return (result == ERROR_SUCCESS);
    }
    
    inline bool SetRegistryValueBinary(HKEY rootKey, const std::string& subKey, const std::string& valueName, const BYTE* data, DWORD dataSize) {
        HKEY hKey;
        LONG result = RegCreateKeyExA(rootKey, subKey.c_str(), 0, NULL, 
                                     REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
        
        if (result != ERROR_SUCCESS) {
            return false;
        }
        
        result = RegSetValueExA(hKey, valueName.c_str(), 0, REG_BINARY, data, dataSize);
        
        RegCloseKey(hKey);
        return (result == ERROR_SUCCESS);
    }
    
    inline bool GetRegistryValueDWORD(HKEY rootKey, const std::string& subKey, const std::string& valueName, DWORD& value) {
        HKEY hKey;
        // Daha yüksek izinler ekle
        REGSAM access = KEY_READ;
        
        // 64-bit sistemlerde 32-bit uygulamalar için gerekli
        #ifdef _WIN64
            // 64-bit uygulama, normal erişim yeterli
        #else
            if (rootKey == HKEY_LOCAL_MACHINE || rootKey == HKEY_CLASSES_ROOT) {
                access |= KEY_WOW64_64KEY; // 64-bit kayıt defterine erişim
            }
        #endif
        
        LONG result = RegOpenKeyExA(rootKey, subKey.c_str(), 0, access, &hKey);
        
        if (result != ERROR_SUCCESS) {
            return false; // Anahtar açılamadı
        }
        
        DWORD dataSize = sizeof(DWORD);
        DWORD type = REG_DWORD;
        result = RegQueryValueExA(hKey, valueName.c_str(), 0, &type, 
                                 reinterpret_cast<BYTE*>(&value), &dataSize);
        
        RegCloseKey(hKey);
        return (result == ERROR_SUCCESS);
    }
    
    inline bool GetRegistryValueString(HKEY rootKey, const std::string& subKey, const std::string& valueName, std::string& value) {
        HKEY hKey;
        // Daha yüksek izinler ekle
        REGSAM access = KEY_READ;
        
        // 64-bit sistemlerde 32-bit uygulamalar için gerekli
        #ifdef _WIN64
            // 64-bit uygulama, normal erişim yeterli
        #else
            if (rootKey == HKEY_LOCAL_MACHINE || rootKey == HKEY_CLASSES_ROOT) {
                access |= KEY_WOW64_64KEY; // 64-bit kayıt defterine erişim
            }
        #endif
        
        LONG result = RegOpenKeyExA(rootKey, subKey.c_str(), 0, access, &hKey);
        
        if (result != ERROR_SUCCESS) {
            return false;
        }
        
        // Önce gereken bufferın boyutunu öğren
        DWORD dataSize = 0;
        result = RegQueryValueExA(hKey, valueName.c_str(), 0, NULL, NULL, &dataSize);
        
        if (result != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return false;
        }
        
        // Yeterli büyüklükte buffer oluştur
        std::vector<char> buffer(dataSize);
        result = RegQueryValueExA(hKey, valueName.c_str(), 0, NULL, 
                                reinterpret_cast<BYTE*>(buffer.data()), &dataSize);
        
        RegCloseKey(hKey);
        
        if (result == ERROR_SUCCESS) {
            // Buffer null-terminated string içeriyor, string'e dönüştür
            value = buffer.data();
            return true;
        }
        
        return false;
    }
    
    inline bool DeleteRegistryValue(HKEY rootKey, const std::string& subKey, const std::string& valueName) {
        HKEY hKey;
        LONG result = RegOpenKeyExA(rootKey, subKey.c_str(), 0, KEY_WRITE, &hKey);
        
        if (result != ERROR_SUCCESS) {
            return false;
        }
        
        result = RegDeleteValueA(hKey, valueName.c_str());
        
        RegCloseKey(hKey);
        return (result == ERROR_SUCCESS);
    }
    
    // Service management
    inline bool ConfigureService(const std::string& serviceName, DWORD startType) {
        SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
        if (!hSCManager) {
            return false;
        }
        
        SC_HANDLE hService = OpenServiceA(hSCManager, serviceName.c_str(), SERVICE_CHANGE_CONFIG);
        if (!hService) {
            CloseServiceHandle(hSCManager);
            return false;
        }
        
        BOOL success = ChangeServiceConfig(
            hService,
            SERVICE_NO_CHANGE,
            startType,
            SERVICE_NO_CHANGE,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        );
        
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        
        return (success == TRUE);
    }
    
    inline bool StartService(const std::string& serviceName) {
        SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
        if (!hSCManager) {
            return false;
        }
        
        SC_HANDLE hService = OpenServiceA(hSCManager, serviceName.c_str(), SERVICE_START);
        if (!hService) {
            CloseServiceHandle(hSCManager);
            return false;
        }
        
        BOOL success = ::StartServiceA(hService, 0, NULL);
        
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        
        return (success == TRUE);
    }
    
    inline bool StopService(const std::string& serviceName) {
        SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
        if (!hSCManager) {
            return false;
        }
        
        SC_HANDLE hService = OpenServiceA(hSCManager, serviceName.c_str(), SERVICE_STOP);
        if (!hService) {
            CloseServiceHandle(hSCManager);
            return false;
        }
        
        SERVICE_STATUS serviceStatus;
        BOOL success = ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
        
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        
        return (success == TRUE);
    }
    
    inline bool IsServiceRunning(const std::string& serviceName) {
        SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
        if (!hSCManager) {
            return false;
        }
        
        SC_HANDLE hService = OpenServiceA(hSCManager, serviceName.c_str(), SERVICE_QUERY_STATUS);
        if (!hService) {
            CloseServiceHandle(hSCManager);
            return false;
        }
        
        SERVICE_STATUS serviceStatus;
        BOOL success = QueryServiceStatus(hService, &serviceStatus);
        
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        
        if (success == TRUE) {
            return (serviceStatus.dwCurrentState == SERVICE_RUNNING);
        }
        
        return false;
    }
    
    // Explorer process management
    inline bool RestartExplorer() {
        // Find Explorer process
        HWND hwnd = FindWindowA("Shell_TrayWnd", NULL);
        if (hwnd == NULL) {
            return false;
        }
        
        // Get Explorer process ID
        DWORD processId;
        GetWindowThreadProcessId(hwnd, &processId);
        if (processId == 0) {
            return false;
        }
        
        // Open process with termination permission
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
        if (hProcess == NULL) {
            return false;
        }
        
        // Terminate Explorer process
        BOOL success = TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
        
        if (!success) {
            return false;
        }
        
        // Wait a moment before starting a new Explorer instance
        Sleep(1000);
        
        // Start a new Explorer process
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        
        if (!CreateProcessA(NULL, (LPSTR)"explorer.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            return false;
        }
        
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        
        return true;
    }
    
    // Open URL with default browser (safer than using cmd)
    inline bool OpenUrl(const std::string& url) {
        return (INT_PTR)ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL) > 32;
    }
    
    // Windows Defender komutları için PowerShell API kullanımı
    inline bool SetDefenderStatus(bool enable) {
        // COM başlatma
        HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
        if (FAILED(hr)) return false;
        
        // Güvenlik başlatma
        hr = CoInitializeSecurity(
            NULL, 
            -1, 
            NULL, 
            NULL, 
            RPC_C_AUTHN_LEVEL_DEFAULT, 
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL, 
            EOAC_NONE, 
            NULL
        );
        
        // Bu hata olabilir ama devam edebiliriz
        if (FAILED(hr) && hr != RPC_E_TOO_LATE) {
            CoUninitialize();
            return false;
        }
        
        // PowerShell komutu oluştur (daha güvenli bir yöntem)
        std::string command = "powershell.exe -Command ";
        command += "\"Set-MpPreference -DisableRealtimeMonitoring ";
        command += enable ? "$false" : "$true";
        command += "\"";
        
        // İşlemi gizli çalıştır
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;
        ZeroMemory(&pi, sizeof(pi));
        
        if (!CreateProcessA(NULL, (LPSTR)command.c_str(), NULL, NULL, FALSE, 
                          CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
            CoUninitialize();
            return false;
        }
        
        // İşlem bitene kadar bekle
        WaitForSingleObject(pi.hProcess, INFINITE);
        
        // Kaynakları temizle
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CoUninitialize();
        
        return true;
    }
    
    // Sanal bellek (Page File) WMI ile ayarlama
    inline bool ConfigureVirtualMemory(bool autoManage, DWORD initialSize = 8192, DWORD maximumSize = 16384) {
        // COM başlatma
        HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
        if (FAILED(hr)) return false;
        
        // Güvenlik başlatma
        hr = CoInitializeSecurity(
            NULL, 
            -1, 
            NULL, 
            NULL, 
            RPC_C_AUTHN_LEVEL_DEFAULT, 
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL, 
            EOAC_NONE, 
            NULL
        );
        
        if (FAILED(hr) && hr != RPC_E_TOO_LATE) {
            CoUninitialize();
            return false;
        }
        
        // WMI bağlantısı oluştur
        IWbemLocator* pLoc = NULL;
        hr = CoCreateInstance(
            CLSID_WbemLocator,
            0,
            CLSCTX_INPROC_SERVER,
            IID_IWbemLocator,
            (LPVOID*)&pLoc
        );
        
        if (FAILED(hr)) {
            CoUninitialize();
            return false;
        }
        
        // WMI servisine bağlan
        IWbemServices* pSvc = NULL;
        hr = pLoc->ConnectServer(
            _bstr_t(L"ROOT\\CIMV2"),
            NULL,
            NULL,
            0,
            NULL,
            0,
            0,
            &pSvc
        );
        
        if (FAILED(hr)) {
            pLoc->Release();
            CoUninitialize();
            return false;
        }
        
        // Güvenlik seviyesini ayarla
        hr = CoSetProxyBlanket(
            pSvc,
            RPC_C_AUTHN_WINNT,
            RPC_C_AUTHZ_NONE,
            NULL,
            RPC_C_AUTHN_LEVEL_CALL,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL,
            EOAC_NONE
        );
        
        if (FAILED(hr)) {
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return false;
        }
        
        // Otomatik yönetim ayarını değiştir
        if (autoManage) {
            // Otomatik yönetimi etkinleştir
            IWbemClassObject* pClass = NULL;
            hr = pSvc->GetObject(_bstr_t(L"Win32_ComputerSystem"), 0, NULL, &pClass, NULL);
            
            if (SUCCEEDED(hr)) {
                // Win32_ComputerSystem instance oluştur
                IWbemClassObject* pInParams = NULL;
                hr = pClass->GetMethod(_bstr_t(L"SetAutomaticManagedPagefile"), 0, &pInParams, NULL);
                
                if (SUCCEEDED(hr)) {
                    // AutomaticManagedPagefile parametresi
                    VARIANT var;
                    VariantInit(&var);
                    var.vt = VT_BOOL;
                    var.boolVal = VARIANT_TRUE;
                    hr = pInParams->Put(_bstr_t(L"AutomaticManagedPagefile"), 0, &var, 0);
                    VariantClear(&var);
                    
                    if (SUCCEEDED(hr)) {
                        // Metodu çağır
                        IWbemClassObject* pOutParams = NULL;
                        hr = pSvc->ExecMethod(_bstr_t(L"Win32_ComputerSystem.Name='%COMPUTERNAME%'"), 
                                            _bstr_t(L"SetAutomaticManagedPagefile"), 0, NULL, pInParams, &pOutParams, NULL);
                        
                        if (pOutParams)
                            pOutParams->Release();
                    }
                    
                    pInParams->Release();
                }
                
                pClass->Release();
            }
        } else {
            // Otomatik yönetimi devre dışı bırak
            IWbemClassObject* pClass = NULL;
            hr = pSvc->GetObject(_bstr_t(L"Win32_ComputerSystem"), 0, NULL, &pClass, NULL);
            
            if (SUCCEEDED(hr)) {
                // Win32_ComputerSystem instance oluştur
                IWbemClassObject* pInParams = NULL;
                hr = pClass->GetMethod(_bstr_t(L"SetAutomaticManagedPagefile"), 0, &pInParams, NULL);
                
                if (SUCCEEDED(hr)) {
                    // AutomaticManagedPagefile parametresi
                    VARIANT var;
                    VariantInit(&var);
                    var.vt = VT_BOOL;
                    var.boolVal = VARIANT_FALSE;
                    hr = pInParams->Put(_bstr_t(L"AutomaticManagedPagefile"), 0, &var, 0);
                    VariantClear(&var);
                    
                    if (SUCCEEDED(hr)) {
                        // Metodu çağır
                        IWbemClassObject* pOutParams = NULL;
                        hr = pSvc->ExecMethod(_bstr_t(L"Win32_ComputerSystem.Name='%COMPUTERNAME%'"), 
                                            _bstr_t(L"SetAutomaticManagedPagefile"), 0, NULL, pInParams, &pOutParams, NULL);
                        
                        if (pOutParams)
                            pOutParams->Release();
                    }
                    
                    pInParams->Release();
                }
                
                pClass->Release();
            }
            
            // Manuel sayfa dosyasını ayarla
            IEnumWbemClassObject* pEnumerator = NULL;
            hr = pSvc->ExecQuery(
                _bstr_t(L"WQL"),
                _bstr_t(L"SELECT * FROM Win32_PageFileSetting WHERE Name='C:\\\\pagefile.sys'"),
                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                NULL,
                &pEnumerator
            );
            
            if (SUCCEEDED(hr)) {
                IWbemClassObject* pPageFile = NULL;
                ULONG uReturn = 0;
                
                if (pEnumerator->Next(WBEM_INFINITE, 1, &pPageFile, &uReturn) == WBEM_S_NO_ERROR && uReturn > 0) {
                    // Boyutları değiştir
                    VARIANT var;
                    VariantInit(&var);
                    var.vt = VT_I4;
                    var.lVal = initialSize;
                    hr = pPageFile->Put(_bstr_t(L"InitialSize"), 0, &var, 0);
                    
                    var.lVal = maximumSize;
                    hr = pPageFile->Put(_bstr_t(L"MaximumSize"), 0, &var, 0);
                    VariantClear(&var);
                    
                    // Değişiklikleri kaydet
                    pSvc->PutInstance(pPageFile, WBEM_FLAG_UPDATE_ONLY, NULL, NULL);
                    
                    pPageFile->Release();
                } else {
                    // Sayfa dosyası yoksa oluştur
                    IWbemClassObject* pClassPageFile = NULL;
                    hr = pSvc->GetObject(_bstr_t(L"Win32_PageFileSetting"), 0, NULL, &pClassPageFile, NULL);
                    
                    if (SUCCEEDED(hr)) {
                        IWbemClassObject* pNewPageFile = NULL;
                        hr = pClassPageFile->SpawnInstance(0, &pNewPageFile);
                        
                        if (SUCCEEDED(hr)) {
                            // Özellikleri ayarla
                            VARIANT var;
                            VariantInit(&var);
                            
                            var.vt = VT_BSTR;
                            var.bstrVal = SysAllocString(L"C:\\pagefile.sys");
                            hr = pNewPageFile->Put(_bstr_t(L"Name"), 0, &var, 0);
                            VariantClear(&var);
                            
                            var.vt = VT_I4;
                            var.lVal = initialSize;
                            hr = pNewPageFile->Put(_bstr_t(L"InitialSize"), 0, &var, 0);
                            
                            var.lVal = maximumSize;
                            hr = pNewPageFile->Put(_bstr_t(L"MaximumSize"), 0, &var, 0);
                            VariantClear(&var);
                            
                            // Yeni sayfa dosyasını kaydet
                            hr = pSvc->PutInstance(pNewPageFile, WBEM_FLAG_CREATE_ONLY, NULL, NULL);
                            
                            pNewPageFile->Release();
                        }
                        
                        pClassPageFile->Release();
                    }
                }
                
                pEnumerator->Release();
            }
        }
        
        // Temizlik
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        
        return true;
    }
    
    // Windows Firewall ayarları
    inline bool ConfigureFirewall(bool enable) {
        // COM başlatma
        HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
        if (FAILED(hr)) return false;
        
        // Güvenlik başlatma
        hr = CoInitializeSecurity(
            NULL, 
            -1, 
            NULL, 
            NULL, 
            RPC_C_AUTHN_LEVEL_DEFAULT, 
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL, 
            EOAC_NONE, 
            NULL
        );
        
        if (FAILED(hr) && hr != RPC_E_TOO_LATE) {
            CoUninitialize();
            return false;
        }
        
        // Firewall servisini başlat/durdur
        if (enable) {
            // Servisin çalıştığından emin ol
            if (!StartService("MpsSvc")) {
                // Servis zaten çalışıyor olabilir - bu bir hata değil
            }
            
            // Güvenilir daha basit yöntem
            std::string command = "netsh advfirewall set allprofiles state on";
            
            // İşlemi gizli çalıştır
            STARTUPINFOA si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_HIDE;
            ZeroMemory(&pi, sizeof(pi));
            
            if (!CreateProcessA(NULL, (LPSTR)command.c_str(), NULL, NULL, FALSE, 
                              CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
                CoUninitialize();
                return false;
            }
            
            // İşlem bitene kadar bekle
            WaitForSingleObject(pi.hProcess, INFINITE);
            
            // Kaynakları temizle
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } else {
            // Firewall'u kapat
            std::string command = "netsh advfirewall set allprofiles state off";
            
            // İşlemi gizli çalıştır
            STARTUPINFOA si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_HIDE;
            ZeroMemory(&pi, sizeof(pi));
            
            if (!CreateProcessA(NULL, (LPSTR)command.c_str(), NULL, NULL, FALSE, 
                              CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
                CoUninitialize();
                return false;
            }
            
            // İşlem bitene kadar bekle
            WaitForSingleObject(pi.hProcess, INFINITE);
            
            // Kaynakları temizle
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        
        CoUninitialize();
        return true;
    }

    // CMD komutlarını gizli çalıştırmak için yardımcı fonksiyon
    inline bool ExecuteCommand(const char* command) {
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE; // Pencereyi gizle
        
        ZeroMemory(&pi, sizeof(pi));
        
        // Komutu çalıştır
        if (!CreateProcessA(NULL, (LPSTR)command, NULL, NULL, FALSE, 
                        CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
            return false;
        }
        
        // İşlem tamamlanana kadar bekle
        WaitForSingleObject(pi.hProcess, INFINITE);
        
        // İşlem handle'larını kapat
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        
        return true;
    }
} 