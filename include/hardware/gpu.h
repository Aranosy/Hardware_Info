#pragma once

#include <string>
#include <vector>
#include "InitWMI.h"

namespace hardware 
{
    class GPU {
    
    public:

        std::string model = WMI::GetWin32_s("Win32_VideoController", "Name");
        std::string vendor = WMI::GetWin32_s("Win32_VideoController", "AdapterCompatibility");
        int64_t driverDate = WMI::GetWin32_d("Win32_VideoController", "DriverDate");
        int64_t driverVersion = WMI::GetWin32_d("Win32_VideoController", "DriverVersion");
        int64_t memoryAmount = WMI::GetWin32_d("Win32_VideoController", "AdapterRAM");
        int64_t memoryType = WMI::GetWin32_d("Win32_VideoController", "VideoMemoryType");
    };
}