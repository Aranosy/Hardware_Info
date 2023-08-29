#include <InitWMI.h>
#include <cpu.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <gpu.h>
#include <disk.h>
#include <os.h>
using namespace hardware::WMI;

int main(void)
{
    hardware::CPU check;
    cout << "------------------- CPU -----------------------\n";
    cout << "CPU model: " << check.model << "\n";
    cout << "CPU vendor: " << check.vendor << "\n";
    cout << "CPU nPhysicalCores: " << check.nPhysicalCores << "\n";
    cout << "CPU nLogicalCores: " << check.nLogicalCores << "\n";
    cout << "CPU currentClockSpeed: " << check.currentClockSpeed << "\n";
    cout << "CPU maxClockSpeed: " << check.maxClockSpeed << "\n";
    cout << "CPU cacheSize: " << check.cacheSize << "\n";
    cout << "-----------------------------------------------\n\n";

    hardware::GPU gpu;
    cout << "------------------- GPU -----------------------\n";
    cout << "GPU model: " << gpu.model[0] << "\n";
    cout << "GPU vendor: " << gpu.vendor[0] << "\n";
    cout << "GPU memoryAmount: " << gpu.memoryAmount[0] << "\n";
    cout << "GPU memoryType: " << gpu.memoryType[0] << "\n";
    cout << "GPU driverVersion: " << gpu.driverVersion[0] << "\n";
    cout << "-----------------------------------------------\n\n";

    hardware::OS os;
    cout << "------------------- OS -----------------------\n";
    cout << "OS os: " << os.getName() << "\n";
    cout << "OS architecture: " << os.architecture << "\n";
    cout << "OS serial number: " << os.serialN << "\n";
    cout << "-----------------------------------------------\n\n";

    hardware::Drives drive;
    cout << "------------------ DRIVES ---------------------\n";
    cout << "Drive name: " << "\"" << drive.name[0] << "\"" << "\n";
    cout << "Drive model: " << drive.model[0] << "\n";
    cout << "Drive vendor: " << drive.vendor[0] << "\n";
    cout << "Drive serial number: " << drive.serialN[0] << "\n";
    cout << "Drive size: " <<   drive.size[0] << "\n";
    cout << "-----------------------------------------------\n";

    return 0;
}