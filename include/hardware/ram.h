#pragma once

#include <string>
#include <windows.h>
#include "../utils/InitWMI.h"

namespace hardware
{
    class RAM {

    public:
        string serialN = WMI::GetWin32<string>("Win32_PhysicalMemory ", "SerialNumber");
        int64_t speed = WMI::GetWin32<int64_t>("Win32_PhysicalMemory ", "Speed");
        string vendor = WMI::GetWin32<string>("Win32_PhysicalMemory ", "Manufacturer");
        string model = WMI::GetWin32<string>("Win32_PhysicalMemory ", "PartNumber");
        int64_t size = WMI::GetSize<int64_t, string>("Win32_PhysicalMemory ", "Capacity", pow(1024, 3));
    };
}