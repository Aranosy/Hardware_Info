#include <string>
#include <windows.h>
#include "InitWMI.h"

namespace hardware
{
    class BaseBoard {

    public:
        string name = WMI::GetWin32<string>("Win32_BaseBoard", "Product");
        string vendor = WMI::GetWin32<string>("Win32_BaseBoard", "Manufacturer");
        string serialN = WMI::GetWin32<string>("Win32_BaseBoard", "SerialNumber");
        string version = WMI::GetWin32<string>("Win32_BaseBoard", "Version");
    };
}