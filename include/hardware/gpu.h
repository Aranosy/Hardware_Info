#pragma once

#include <string>
#include <vector>
#include "InitWMI.h"

namespace hardware 
{
    class GPU {
    
    public:
        vector<string> model = WMI::GetWin32<vector<string>>("Win32_VideoController", "Name");
        vector<string> vendor = WMI::GetWin32<vector<string>>("Win32_VideoController", "AdapterCompatibility");
        vector<int64_t> memoryAmount = WMI::GetWin32<vector<int64_t>>("Win32_VideoController", "AdapterRAM");
        vector<int64_t> memoryType = WMI::GetWin32<vector<int64_t>>("Win32_VideoController", "VideoMemoryType");
        vector<string> driverVersion = WMI::GetWin32<vector<string>>("Win32_VideoController", "DriverVersion");
    };
}