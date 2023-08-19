#include <InitWMI.h>
#include <cpu.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <gpu.h>
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
    cout << "CPU cacheSize: " << check.cacheSize << "\n\n";

    hardware::GPU gpu;
    cout << "------------------- GPU -----------------------\n";
    cout << "GPU model: " << gpu.model << "\n";
    cout << "GPU vendor: " << gpu.vendor << "\n";
    cout << "GPU driverDate: " << gpu.driverDate << "\n";
    cout << "GPU driverVersion: " << gpu.driverVersion << "\n";
    cout << "GPU memoryAmount: " << gpu.memoryAmount << "\n";
    cout << "GPU memoryType: " << gpu.memoryType << "\n\n";

    hardware::OS os;
    cout << "------------------- OS -----------------------\n";
    cout << "OS os: " << os.getName() << "\n";
    cout << "OS architecture: " << os.architecture << "\n";
    cout << "-----------------------------------------------\n";

    return 0;
}