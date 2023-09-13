#include <InitWMI.h>
#include <cpu.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <gpu.h>
#include <disk.h>
#include <os.h>
#include <ram.h>
#include <base_board.h>

using namespace hardware;
using namespace WMI;

int main(void)
{
    CPU check;
    cout << "------------------- CPU -----------------------\n";
    cout << "CPU model: " << check.model << "\n";
    cout << "CPU vendor: " << check.vendor << "\n";
    cout << "CPU nPhysicalCores: " << check.nPhysicalCores << "\n";
    cout << "CPU nLogicalCores: " << check.nLogicalCores << "\n";
    cout << "CPU currentClockSpeed: " << check.currentClockSpeed << "\n";
    cout << "CPU maxClockSpeed: " << check.maxClockSpeed << "\n";
    cout << "CPU cacheSize: " << check.cacheSize << "\n";
    cout << "-----------------------------------------------\n\n";

    GPU gpu;
    cout << "------------------- GPU -----------------------\n";
    cout << "GPU model: " << gpu.model[0] << "\n";
    cout << "GPU vendor: " << gpu.vendor[0] << "\n";
    cout << "GPU memoryAmount: " << gpu.memoryAmount[0] << "\n";
    cout << "GPU memoryType: " << gpu.memoryType[0] << "\n";
    cout << "GPU driverVersion: " << gpu.driverVersion[0] << "\n";
    cout << "-----------------------------------------------\n\n";

    OS os;
    cout << "------------------- OS -----------------------\n";
    cout << "OS os: " << os.getName() << "\n";
    cout << "OS architecture: " << os.architecture << "\n";
    cout << "OS serial number: " << os.serialN << "\n";
    cout << "-----------------------------------------------\n\n";

    Drives drive;
    cout << "------------------ DRIVES ---------------------\n";
    cout << "Drive name: "
         << "\"" << drive.name[0] << "\""
         << "\n";
    cout << "Drive model: " << drive.model[0] << "\n";
    cout << "Drive vendor: " << drive.vendor[0] << "\n";
    cout << "Drive serial number: " << drive.serialN[0] << "\n";
    cout << "Drive size: " << drive.size[0] << " Gb"
         << "\n";
    cout << "Drive free space: " << drive.freeSpace[0] << " Gb"
         << "\n";
    cout << "Drive file system: " << drive.fileSystem[0] << "\n";
    cout << "-----------------------------------------------\n\n";

    RAM ram;
    cout << "-------------------- RAM ----------------------\n";
    cout << "speed: " << ram.speed << "\n";
    cout << "serialN: " << ram.serialN << "\n";
    cout << "-----------------------------------------------\n\n";

    BaseBoard baseBoard;
    cout << "------------------ Base Board -----------------\n";
    cout << "name: " << baseBoard.name << "\n";
    cout << "vendor: " << baseBoard.vendor << "\n";
    cout << "version: " << baseBoard.version << "\n";
    cout << "serialN: " << baseBoard.serialN << "\n";
    cout << "-----------------------------------------------\n\n";
    
    return 0;
}