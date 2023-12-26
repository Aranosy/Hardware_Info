#pragma once

#include <string>
#include <windows.h>
#include "../utils/InitWMI.h"

namespace hardware 
{
    class OS {
    
    public:

    string architecture = WMI::GetWin32<string>("Win32_OperatingSystem", "OSArchitecture");
    string serialN = WMI::GetWin32<string>("Win32_OperatingSystem", "SerialNumber");
    string os = getName();
    string name = WMI::GetWin32<string>("Win32_ComputerSystem", "Name");
    string getName()
    {
        string fullName = WMI::GetWin32<string>("Win32_OperatingSystem", "Name");
        string ret;
        for(int i = 0; i < fullName.length(); i++)
        {
            if(fullName[i] == '|')
            {
                ret = fullName.substr(0, i);
                break;
            }
        }

        return  ret + " (" + "build " + WMI::GetWin32<string>("Win32_OperatingSystem", "BuildNumber") + ")";
    }       

    };
}