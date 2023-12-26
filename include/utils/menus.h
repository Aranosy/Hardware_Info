#include <string>
#include <vector>
#include <variant>
#include "C:\Users\artem\hwinfo_CS50\include\hardware\hardware.h"
using namespace std;
using namespace hardware;

struct linkMenu
{
    string point;
    vector<string> info;
};

linkMenu SetLinkMenu(string p, vector<string> nm)
{
    linkMenu ret;
    ret.point = p;
    ret.info = nm;

    return ret;
}

struct menu
{
    string name;
    vector<linkMenu> links;
};

menu SetMenu(string name, vector<linkMenu> l)
{
    menu ret;
    ret.name = name;
    ret.links = l;

    return ret;
}

vector<string> start_info{"WELCOME",
                          "This aplication created for Hardward CS50 2023 by Miroshnychenko Artem.",
                          "Aplication outputs hardware information about your computer. To get instructions how",
                          "to use program, enter HELP."};

BaseBoard bb;
vector<string> bbInfo = {
    "Model: " + bb.name,
    "Manufacturer: " + bb.vendor,
    "Serial number: " + bb.serialN,
    "Version: " + bb.version};

CPU cpu;
vector<string> cpuInfo = {
    "Model: " + cpu.model,
    "Manufacturer: " + cpu.vendor,
    "Number of physical cores: " + to_string(cpu.nPhysicalCores),
    "Number of logical cores: " + to_string(cpu.nLogicalCores),
    "Current clock speed: " + to_string(cpu.currentClockSpeed) + "MHz",
    "Maximal clock speed: " + to_string(cpu.maxClockSpeed) + "MHz",
    "Chache size: " + to_string(cpu.cacheSize)};

Drives drives;
vector<string> SetUpDisk()
{
    vector<string> diskT;
    for (int i = 0; i < drives.disks.size(); i++)
    {
        diskT.push_back("Device ID: " + drives.disks[i].deviceID);
        diskT.push_back("Model: " + drives.disks[i].model);
        diskT.push_back("Serial number: " + drives.disks[i].serialN);
        diskT.push_back("Size: " + to_string(drives.disks[i].size));
        diskT.push_back("Bus type: " + drives.disks[i].busType);
        diskT.push_back("Media type: " + drives.disks[i].mediaType);
        diskT.push_back("");

        for (int a = 0; a < drives.disks[i].partions.size(); a++)
        {
            Drives::Disk::Partions p = drives.disks[i].partions[a];
            diskT.push_back("PARTION " + to_string(a));
            diskT.push_back("Volume: " + p.volume);
            diskT.push_back("Total space: " + to_string(p.totalSpace));
            diskT.push_back("Free space: " + to_string(p.freeSpace));
            diskT.push_back("File system: " + p.fileSystem);
            diskT.push_back("");
        }
    }

    return diskT;
}
vector<string> diskInfo = SetUpDisk();

GPU gpu;
vector<string> SetUpGPU()
{
    vector<string> gpuT;
    for (int i = 0; i < gpu.driverVersion.size(); i++)
    {
        gpuT.push_back("Model: " + gpu.model[i]);
        gpuT.push_back("Manufacturer: " + gpu.vendor[i]);
        gpuT.push_back("Memory amount: " + to_string(gpu.memoryAmount[i]));
        gpuT.push_back("Driver version: " + gpu.driverVersion[i]);
        gpuT.push_back("Current refresh rate: " + to_string(gpu.refreshRate[i]));
        gpuT.push_back("Resolution: " + gpu.resolution[i]);
    }
    return gpuT;
}
vector<string> gpuInfo = SetUpGPU();

OS os;
vector<string> osInfo = {
    "Name: " + os.os,
    "Architecture: " + os.architecture,
    "Serial Number: " + os.serialN,
    "Desktop name: " + os.name};

RAM ram;
vector<string> ramInfo = {
    "Model: " + ram.model,
    "Manufacturer: " + ram.vendor,
    "Capacity: " + to_string(ram.size) + "GB",
    "Speed: " + to_string(ram.speed) + " ns",
    "Serial Number: " + ram.serialN};

vector<string> temp;

vector<string> helpInfo = {
    "Navigation through the program is facilitated by the menu on the left side and various",
    "commands. To select a menu option, simply type its corresponding number. For example",
    "to choose Base Board from the start menu, type 1. To navigate between pages, use next",
    "or past. Typing next will take you to the next page, while past will take you to",
    "the previous one.",
    "",
    "Once you've selected a menu option, the information will be displayed on the right-side",
    "menu. Simultaneously, a new menu will appear on the left side. If you choose 1, you",
    "will return to the start. Alternatively, selecting 2 will save the displayed",
    "information to a log file in the program folder. You can specify the file path by typing",
    "it, separated by spaces. If the path contains spaces, enclose it in quotation marks.",
    "For instance: 2 C:\\LogFiles or 2 \"C:\\Log Files\"."};

linkMenu helpM = SetLinkMenu("HELP", helpInfo);
linkMenu baseBoardM = SetLinkMenu("BASE BOARD", bbInfo);
linkMenu cpuM = SetLinkMenu("CPU", cpuInfo);
linkMenu diskM = SetLinkMenu("DISK", diskInfo);
linkMenu gpuM = SetLinkMenu("GPU", gpuInfo);
linkMenu osM = SetLinkMenu("OS", osInfo);
linkMenu ramM = SetLinkMenu("RAM", ramInfo);
linkMenu allM = SetLinkMenu("OUTPUT ALL", temp);
linkMenu exitM = SetLinkMenu("EXIT", temp);

// vector<linkMenu> start_links = {helpM, baseBoardM, cpuM, diskM, gpuM, osM, ramM, allM, logM, exitM};
vector<menu> start_links = {SetMenu("HARDWARE", {baseBoardM, cpuM, diskM, gpuM, osM, ramM}), SetMenu("UTILS", {helpM, allM, exitM})};