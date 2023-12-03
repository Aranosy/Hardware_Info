#include <string>
#include <vector>
#include <variant>
#include <hardware.h>
using namespace std;
using namespace hardware;


struct outMenu
{
    string point;
    string info;
};

outMenu SetOutMenu(string p, string i)
{
    outMenu ret;
    ret.info = i;
    ret.point = p;

    return ret;
}

struct linkMenu
{
    string point;
    vector<outMenu> next_menus;
    vector<vector<outMenu>> next_menusV;
};

linkMenu SetLinkMenu(string p, vector<outMenu> n = {}, vector<vector<outMenu>> nV = {})
{
    linkMenu ret;
    ret.point = p;  
    if (n.empty())
        ret.next_menusV = nV;
    else
        ret.next_menus = n;

    return ret;
}


vector<string> start_info{"WELCOME",
                          "Hardware info is aplication created for Hardward CS50 2023 by Miroshnychenko Artem.",
                          "Aplication outputs hardware information about your computer. You can select menu point",
                          "on the left-side by typing number of it. To get instructions how to use program, enter",
                          "1 that gets you to HELP menu."};
vector<outMenu> temp;
vector<vector<outMenu>> tempO;
BaseBoard bb;
vector<outMenu> bbInfo = {
    SetOutMenu("MODEL", "Model: " + bb.name),
    SetOutMenu("MANUFACTURER", "Manufacturer: " + bb.vendor),
    SetOutMenu("SERIAL NUMBER", "Serial number: " + bb.serialN),
    SetOutMenu("VERSION", "Version: " + bb.version)};

CPU cpu;
vector<outMenu> cpuInfo = {
    SetOutMenu("MODEL", "Model: " + cpu.model),
    SetOutMenu("MANUFACTURER", "Manufacturer: " + cpu.vendor),
    SetOutMenu("SERIAL NUMBER", "Serial number: " + cpu.serialN),
    SetOutMenu("PHYSICAL CORES", "Number of physical cores: " + cpu.nPhysicalCores),
    SetOutMenu("LOGICAL CORES", "Number of logical cores: " + cpu.nLogicalCores),
    SetOutMenu("CUR CLOCK SPEED", "Current clock speed: " + to_string(cpu.currentClockSpeed) + "MHz"),
    SetOutMenu("MAX CLOCK SPEED", "Maximal clock speed: " + to_string(cpu.maxClockSpeed) + "MHz"),
    SetOutMenu("CHACHE SIZE", "Chache size: " + to_string(cpu.cacheSize) + "BYTES")};

vector<vector<outMenu>> diskInfo;
vector<vector<outMenu>> gpuInfo;

OS os;
vector<outMenu> osInfo = {
    SetOutMenu("NAME", "Name: " + os.os),
    SetOutMenu("ARCHITECTURE", "Architecture: " + os.architecture),
    SetOutMenu("SERIAL NUMBER", "Serial Number: " + os.serialN),
    SetOutMenu("DESKTOP NAME", "Desktop name" + os.name)};

RAM ram;
vector<outMenu> ramInfo = {
    SetOutMenu("MODEL", "Model: " + ram.model),
    SetOutMenu("MANUFACTURER", "Manufacturer: " + ram.vendor),
    SetOutMenu("CAPACITY", "Capacity: " + to_string(ram.size) + "GB"),
    SetOutMenu("SPEED", "Speed: " + to_string(ram.speed) + "nanoseconds"),
    SetOutMenu("SERIAL NUMBER", "Serial Number" + ram.serialN)};

linkMenu helpM = SetLinkMenu("HELP", temp);
linkMenu baseBoardM = SetLinkMenu("BASE BOARD", temp);
linkMenu cpuM = SetLinkMenu("CPU", temp);
linkMenu diskM = SetLinkMenu("DISK", {}, tempO);
linkMenu gpuM = SetLinkMenu("GPU", {}, tempO);
linkMenu osM = SetLinkMenu("OS", temp);
linkMenu ramM = SetLinkMenu("RAM", temp);
linkMenu allM = SetLinkMenu("OUTPUT ALL", temp);
linkMenu logM = SetLinkMenu("SAVE LOG", temp);
linkMenu exitM = SetLinkMenu("EXIT", temp);

vector<linkMenu> start_links = {helpM, baseBoardM, cpuM, diskM, gpuM, osM, ramM, allM, logM, exitM};