#include <InitWMI.h>
#include <cpu.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <gpu.h>
#include <os.h>
#include <ram.h>
#include <base_board.h>
#include <algorithm>

using namespace hardware;
using namespace WMI;

vector<string> drivesLetters = WMI::wmi_getDriveLetters();
vector<vector<string>> ret;
bool physicDriveSort(string f, string s)
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

string getVolume(string drive, string pDrive)
{
    string partion;

    for (int b = 19 + pDrive.length(); b < drive.length(); b++)
        if (isdigit(drive[b]))
            partion += drive[b];
        else
            break;

    return drive.substr(20 + pDrive.length() + partion.length());
}

int main(void)
{
    // // Get physical drives count
    // vector<string> physicalDrives;
    // string temp = "";
    // for (auto i : drivesLetters)
    // {
    //     for (int b = 6; b < i.length(); b++)
    //         if (isdigit(i[b]))
    //             temp += i[b];
    //         else
    //             break;
    //     physicalDrives.push_back(temp);
    //     temp = "";
    // }
    sort(drivesLetters.begin(), drivesLetters.end(), physicDriveSort);
    vector<vector<string>> diskDrives(drivesLetters.size());
    for (int i = 0; i < drivesLetters.size(); i++)
    {
        string pDrive = getPhysicalDrive(drivesLetters[i]);
        string volume = getVolume(drivesLetters[i], pDrive);
        diskDrives[stoi(pDrive)].push_back(volume);
    }

    for (int i = 0; i < stoi(getPhysicalDrive(drivesLetters[drivesLetters.size() - 1])) + 1; i++)
    {
        cout << "Physical drive " << i << ":" << "\n";
        for (auto i: diskDrives[i])
            cout << "Volume: " << i << "\n";
    }
    cout << "Press Enter to End..." << endl;
    cin.ignore(); // ends after the user hits enter
    return 0;
}
