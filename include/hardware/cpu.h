#pragma once

#include <string>
#include <vector>

#include "../utils/InitWMI.h"

namespace hardware 
{
    class CPU {
    
    public:

        string model = WMI::GetWin32<string>("Win32_Processor", "Name");
        string vendor = WMI::GetWin32<string>("Win32_Processor", "Manufacturer");
        int64_t nPhysicalCores = WMI::GetWin32<int64_t>("Win32_Processor", "NumberOfCores");
        int64_t nLogicalCores = WMI::GetWin32<int64_t>("Win32_Processor", "NumberOfLogicalProcessors");
        int64_t currentClockSpeed = WMI::GetWin32<int64_t>("Win32_Processor", "CurrentClockSpeed");
        int64_t maxClockSpeed = WMI::GetWin32<int64_t>("Win32_Processor", "MaxClockSpeed");
        int64_t cacheSize = WMI::GetWin32<int64_t>("Win32_Processor", "L3CacheSize") * 1024;

    };


}