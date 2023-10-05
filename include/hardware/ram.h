#include <string>
#include <windows.h>
#include "InitWMI.h"

namespace hardware
{
    class RAM {

    public:
        string serialN = WMI::GetWin32<string>("Win32_PhysicalMemory ", "SerialNumber");
        int64_t speed = WMI::GetWin32<int64_t>("Win32_PhysicalMemory ", "Speed");
    };
}