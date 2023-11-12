#include <string>
#include <windows.h>
#include <algorithm>
#include "InitWMI.h"

namespace hardware
{
    class Drives
    {
    public:
        vector<string> drivesLetters = WMI::wmi_getDriveLetters();
        class Disk
        {
        public:
            class Partions
            {
            public:
                string volume;
                long long totalSpace;
                long long freeSpace;
                string fileSystem;
            };

            string model;
            string serialN;
            vector<Partions> partions;
            long long size;
            string busType;
            string mediaType;
            string deviceID;
        };
        vector<Disk> disks = getInfo();

        vector<long long> GetSize(string table, string field)
        {
            vector<long long> ret;
            for (auto i : WMI::GetWin32<vector<string>>(table, field))
                ret.push_back(strtoll(i.c_str(), NULL, 10) / 1000000000);
            return ret;
        }

        static bool physicDriveSort(string f, string s)
        {
            vector<string> pDrives;
            vector<string> drives = {f, s};
            string temp = "";
            for (int i = 0; i < 2; i++)
            {
                temp = "";
                for (int b = 6; b < drives[i].length(); b++)
                    if (isdigit(drives[i][b]))
                        temp += drives[i][b];
                    else
                        break;
                pDrives.push_back(temp);
            }
            temp = "";
            return stoi(pDrives[0]) < stoi(pDrives[1]);
        }

        string getPhysicalDrive(string drive)
        {
            string ret;
            for (int b = 6; b < drive.length(); b++)
                if (isdigit(drive[b]))
                    ret += drive[b];
                else
                    break;
            return ret;
        }

        string getVolume(const string &drive, const string &pDrive)
        {
            string partion;

            for (size_t b = 19 + pDrive.length(); b < drive.length(); b++)
                if (isdigit(drive[b]))
                    partion += drive[b];
                else
                    break;

            return drive.substr(20 + pDrive.length() + partion.length());
        }

        int find_drive(string &volume, vector<vector<string>> diskDrives)
        {
            for (size_t i = 0; i < diskDrives.size(); i++)
                for (size_t d = 0; d < diskDrives[i].size(); d++)
                    if (volume == diskDrives[i][d])
                        return i;
        }

        vector<Disk> getInfo()
        {

            // Get sorted vector of disk partions
            sort(drivesLetters.begin(), drivesLetters.end(), physicDriveSort);
            vector<vector<string>> diskDrives(drivesLetters.size());
            for (int i = 0; i < drivesLetters.size(); i++)
            {
                string pDrive = getPhysicalDrive(drivesLetters[i]);
                string volume = getVolume(drivesLetters[i], pDrive);
                diskDrives[stoi(pDrive)].push_back(volume);
            }

            vector<Disk> ret(stoi(getPhysicalDrive(drivesLetters[drivesLetters.size() - 1])) + 1);

            // Query for every physical drive and partion
            vector<string> volumes = WMI::GetWin32<vector<string>>("Win32_LogicalDisk", "Name");
            vector<string> fileSystems = WMI::GetWin32<vector<string>>("Win32_LogicalDisk", "FileSystem");

            vector<string> pDrives = WMI::GetWin32<vector<string>>("Win32_DiskDrive", "DeviceID");
            vector<string> models = WMI::GetWin32<vector<string>>("Win32_DiskDrive", "Model");
            vector<string> serialNs = WMI::GetWin32<vector<string>>("Win32_DiskDrive", "SerialNumber");
            vector<long long> size = GetSize("Win32_DiskDrive", "Size");

            string media[4] = {"Unspecified", "HDD", "SSD", "SCM"};
            string buses[18] = {"The bus type is unknown.", "SCSI", "ATAPI", "ATA", "IEEE 1394", "SSA", "Fibre Channel", "USB",
                                "RAID", "iSCSI", "Serial Attached SCSI (SAS)", "Serial ATA (SATA)", "Secure Digital (SD)",
                                "Multimedia Card (MMC)", "This value is reserved for system use.", "File-Backed Virtual", "Storage spaces", "NVMe"};
            vector<int64_t> pDrivesM = WMI::GetWin32<vector<int64_t>>("MSFT_Disk", "Number", "ROOT\\Microsoft\\Windows\\Storage");
            vector<int64_t> busTypes = WMI::GetWin32<vector<int64_t>>("MSFT_Disk", "BusType", "ROOT\\Microsoft\\Windows\\Storage");
            vector<int64_t> mediaTypes = WMI::GetWin32<vector<int64_t>>("MSFT_PhysicalDisk", "MediaType", "ROOT\\Microsoft\\Windows\\Storage");
            for (int i = 0; i < mediaTypes.size(); i++)
                if (mediaTypes[i] > 2)
                    mediaTypes[i] = mediaTypes[i] - 2;

            // Put physical drives info
            for (int i = 0; i < pDrives.size(); i++)
            {
                string currentDiskDrive;
                for (int p = 17; p < pDrives[i].size(); p++)
                    if (isdigit(pDrives[i][p]))
                        currentDiskDrive += pDrives[i][p];
                    else
                        break;

                // Put disk drive info
                int cdd = stoi(currentDiskDrive);
                ret[stoi(currentDiskDrive)].model = models[i];
                ret[stoi(currentDiskDrive)].serialN = serialNs[i];
                ret[stoi(currentDiskDrive)].size = size[i];
                ret[stoi(currentDiskDrive)].deviceID = pDrives[i];

                // Put MSFT info
                ret[pDrivesM[i]].busType = buses[busTypes[i]];
                ret[pDrivesM[i]].mediaType = media[mediaTypes[i]];
            }

            // Put partions info
            for (int i = 0; i < volumes.size(); i++)
            {
                Drives::Disk::Partions p;
                p.fileSystem = fileSystems[i];
                p.volume = volumes[i];
                ULARGE_INTEGER lpFreeBytesAvailable;
                ULARGE_INTEGER lpTotalNumberOfBytes;
                GetDiskFreeSpaceEx(
                    volumes[i].c_str(),
                    &lpFreeBytesAvailable,
                    &lpTotalNumberOfBytes,
                    nullptr);
                p.totalSpace = lpTotalNumberOfBytes.QuadPart / pow(1024, 3);
                p.freeSpace = lpFreeBytesAvailable.QuadPart / pow(1024, 3);

                ret[find_drive(volumes[i], diskDrives)].partions.push_back(p);
            }

            return ret;
        }
    };
}