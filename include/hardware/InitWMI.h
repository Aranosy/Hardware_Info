#pragma once

#define _WIN32_DCOM
#include <iostream>
#include <wbemidl.h>
#include <comdef.h>
#pragma comment(lib, "wbemuuid.lib")
#include <string>
#include <vector>

using namespace std;

namespace hardware
{
    namespace WMI
    {
        IWbemLocator *pLoc = NULL;
        IWbemServices *pSvc = NULL;

        BOOL wmi_run(HRESULT hres)
        {

            // Initialize COM. ------------------------------------------

            hres = CoInitializeEx(0, COINIT_MULTITHREADED);
            if (FAILED(hres))
            {
                cout << "Failed to initialize COM library. Error code = 0x"
                     << hex << hres << endl;
                return 1; // Program has failed.
            }

            // Set general COM security levels --------------------------


            hres = CoInitializeSecurity(
                NULL,
                -1,                          // COM authentication
                NULL,                        // Authentication services
                NULL,                        // Reserved
                RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
                RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
                NULL,                        // Authentication info
                EOAC_NONE,                   // Additional capabilities
                NULL                         // Reserved
            );

            if (FAILED(hres))
            {
                cout << "Failed to initialize security. Error code = 0x"
                     << hex << hres << endl;
                CoUninitialize();
                return 1; // Program has failed.
            }

            // Obtain the initial locator to WMI -------------------------

            // IWbemLocator *pLoc = NULL;

            hres = CoCreateInstance(
                CLSID_WbemLocator,
                0,
                CLSCTX_INPROC_SERVER,
                IID_IWbemLocator, (LPVOID *)&pLoc);

            if (FAILED(hres))
            {
                cout << "Failed to create IWbemLocator object."
                     << " Err code = 0x"
                     << hex << hres << endl;
                CoUninitialize();
                return 1; // Program has failed.
            }


            // Connect to WMI through the IWbemLocator::ConnectServer method

            // IWbemServices *pSvc = NULL;

            // Connect to the root\cimv2 namespace with
            // the current user and obtain pointer pSvc
            // to make IWbemServices calls.
            hres = pLoc->ConnectServer(
                _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
                NULL,                    // User name. NULL = current user
                NULL,                    // User password. NULL = current
                0,                       // Locale. NULL indicates current
                NULL,                    // Security flags.
                0,                       // Authority (e.g. Kerberos)
                0,                       // Context object
                &pSvc                    // pointer to IWbemServices proxy
            );

            if (FAILED(hres))
            {
                cout << "Could not connect. Error code = 0x"
                     << hex << hres << endl;
                pLoc->Release();
                CoUninitialize();
                return 1; // Program has failed.
            }


            // Set security levels on the proxy -------------------------

            hres = CoSetProxyBlanket(
                pSvc,                        // Indicates the proxy to set
                RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
                RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
                NULL,                        // Server principal name
                RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
                RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
                NULL,                        // client identity
                EOAC_NONE                    // proxy capabilities
            );

            if (FAILED(hres))
            {
                cout << "Could not set proxy blanket. Error code = 0x"
                     << hex << hres << endl;
                pSvc->Release();
                pLoc->Release();
                CoUninitialize();
                return 1; // Program has failed.
            }
            return 0;
        }

        BOOL wmi_close()
        {
            // Cleanup
            // ========

            pSvc->Release();
            pLoc->Release();
            CoUninitialize();

            return 0; // Program successfully completed.
        }

        template <typename T>
        void WMIExec(const string &table, string field, vector<T> &var,
                     const string &server = "root/cimv2")
        {
            HRESULT hres = NULL;
            wmi_run(hres);

            // Use the IWbemServices pointer to make requests of WMI.
            // Make requests here:
            string query("SELECT " + field + " FROM " + table);

            IEnumWbemClassObject *pEnumerator = NULL;
            hres = pSvc->ExecQuery(
                bstr_t("WQL"),
                bstr_t(std::wstring(query.begin(), query.end()).c_str()),
                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                NULL,
                &pEnumerator);
            if (FAILED(hres))
            {
                cout << "Query for processes failed. "
                     << "Error code = 0x"
                     << hex << hres << endl;
                pSvc->Release();
                pLoc->Release();
                CoUninitialize();
                return; // Program has failed.
            }

            IWbemClassObject *pclsObj;
            ULONG uReturn = 0;


            while (pEnumerator)
            {
                hres = pEnumerator->Next(WBEM_INFINITE, 1,
                                         &pclsObj, &uReturn);

                if (0 == uReturn)
                {
                    break;
                }

                VARIANT vtProp;
                pclsObj->Get(std::wstring(field.begin(), field.end()).c_str(), 0, &vtProp, nullptr, nullptr);

                if (std::is_same<T, long>::value || std::is_same<T, int>::value)
                    var.push_back((T)vtProp.intVal);
                else if (std::is_same<T, bool>::value)
                    var.push_back((T)vtProp.boolVal);
                else if (std::is_same<T, unsigned>::value)
                    var.push_back((T)vtProp.uintVal);
                else if (std::is_same<T, unsigned short>::value)
                    var.push_back((T)vtProp.uiVal);
                else if (std::is_same<T, long long>::value)
                    var.push_back((T)vtProp.llVal);
                else if (std::is_same<T, unsigned long long>::value)
                    var.push_back((T)vtProp.ullVal);
                else
                    var.push_back((T)((bstr_t)vtProp.bstrVal).copy());

                pclsObj->Release();
                pclsObj = NULL;
            }
            wmi_close();
        }

        template <typename T>
        T GetWin32(const string &table, string field)
        {

            if constexpr (is_same<T, string>::value || is_same<T, vector<string>>::value)
            {
                std::vector<const wchar_t *> var{};
                std::vector<std::string> ret;
                WMIExec(table, field, var);
                ret.reserve(var.size());
                for (auto &v : var)
                {
                    if (v == nullptr)
                        continue;
                    std::wstring tmp(v);
                    ret.emplace_back(tmp.begin(), tmp.end());
                }

                if constexpr (is_same<T, string>::value)
                    return ret[0];
                else
                    return ret;
            }
            else if constexpr (is_same<T, int64_t>::value || is_same<T, vector<int64_t>>::value)
            {
                std::vector<int64_t> var{};
                WMIExec(table, field, var);
                std::vector<int64_t> ret;
                ret.reserve(var.size());
                for (auto &v : var)
                    ret.push_back(v);

                if constexpr (is_same<T, int64_t>::value)
                    return ret[0];
                else
                    return ret;
            }
        }

        vector<long long> GetSize(string table, string field)
        {
            vector<long long> ret;
            for (auto i : WMI::GetWin32<vector<string>>(table, field))
                ret.push_back(strtoll(i.c_str(), NULL, 10) / 1000000000);
            return ret;
        }

    }
}