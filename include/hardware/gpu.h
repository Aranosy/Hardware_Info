#pragma once

#include <string>
#include <vector>
#include "../utils/InitWMI.h"

namespace hardware 
{
    class GPU {
    
    public:
        vector<string> model = WMI::GetWin32<vector<string>>("Win32_VideoController", "Name");
        vector<string> vendor = WMI::GetWin32<vector<string>>("Win32_VideoController", "AdapterCompatibility");
        vector<int64_t> memoryAmount = WMI::GetSize<vector<int64_t>, int64_t>("Win32_VideoController", "AdapterRAM", (1024 * 1024));
        vector<string> driverVersion = WMI::GetWin32<vector<string>>("Win32_VideoController", "DriverVersion");
        vector<int64_t> xRes = WMI::GetWin32<vector<int64_t>>("Win32_VideoController", "CurrentHorizontalResolution");
        vector<int64_t> yRes = WMI::GetWin32<vector<int64_t>>("Win32_VideoController", "CurrentVerticalResolution");
        vector<int64_t> refreshRate = WMI::GetWin32<vector<int64_t>>("Win32_VideoController", "CurrentRefreshRate");

        vector<string> SetRes()
        {
            vector<string> ret;
            for (int i = 0; i < xRes.size(); i++)
                ret.push_back(to_string(xRes[i]) + "x" + to_string(yRes[i]));

            return ret;
        }
        
        vector<string> resolution = SetRes();
    };  
}