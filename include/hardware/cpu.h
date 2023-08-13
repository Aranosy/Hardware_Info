#pragma once

#include <string>
#include <vector>
#include "InitWMI.h"

namespace hardware 
{
    class CPU {
    
    public:

        std::string model = WMI::GetWin32_s("Win32_Processor", "Name");
        std::string vendor = WMI::GetWin32_s("Win32_Processor", "Manufacturer");
        int64_t nPhysicalCores = WMI::GetWin32_d("Win32_Processor", "NumberOfCores");
        int64_t nLogicalCores = WMI::GetWin32_d("Win32_Processor", "NumberOfLogicalProcessors");
        int64_t currentClockSpeed = WMI::GetWin32_d("Win32_Processor", "CurrentClockSpeed");
        int64_t maxClockSpeed = WMI::GetWin32_d("Win32_Processor", "MaxClockSpeed");
        int64_t cacheSize = WMI::GetWin32_d("Win32_Processor", "L3CacheSize") * 1024;

    };
}