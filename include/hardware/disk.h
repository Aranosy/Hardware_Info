#include <string>
#include <windows.h>
#include "InitWMI.h"

namespace hardware 
{
    class Drives {
    
    public:
        vector<string> name = WMI::GetWin32<vector<string>>("Win32_LogicalDisk", "Name");
        vector<string> model = WMI::GetWin32<vector<string>>("Win32_DiskDrive", "Model");
        vector<string> vendor = WMI::GetWin32<vector<string>>("Win32_DiskDrive", "Manufacturer");
        vector<long long> size = WMI::GetSize("Win32_DiskDrive", "Size");
        vector<long long> freeSpace = WMI::GetSize("Win32_LogicalDisk", "FreeSpace");
        vector<string> fileSystem = WMI::GetWin32<vector<string>>("Win32_LogicalDisk", "FileSystem");
        vector<string> serialN = WMI::GetWin32<vector<string>>("Win32_DiskDrive", "SerialNumber"); 
    };
}