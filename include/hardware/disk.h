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
        vector<long long> size = getSize("Win32_DiskDrive", "Size");
        vector<long long> freeSpace = getSize("Win32_LogicalDisk", "FreeSpace");
        vector<string> fileSystem = WMI::GetWin32<vector<string>>("Win32_LogicalDisk", "FileSystem");
        vector<string> serialN = WMI::GetWin32<vector<string>>("Win32_DiskDrive", "SerialNumber"); 
    private:
        vector<long long> getSize(string table, string field)
        {
            vector<long long> ret;
            for (auto i: WMI::GetWin32<vector<string>>(table, field))
            {
                ret.push_back(strtoll(i.c_str(), NULL, 10) / 1000000000);
            }

            return ret;
        }
    };
}