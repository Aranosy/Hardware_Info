#include <InitWMI.h>
#include <cpu.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

using namespace hardware::WMI;

int main(void)
{
    hardware::CPU check;
    // Set CP1251 instead of default CP866 to output Cyrillic text.    
    cout << "------------------- CPU -----------------------\n";
    cout << "CPU model: " << check.model << "\n";
    cout << "CPU vendor: " << check.vendor << "\n";
    cout << "CPU nPhysicalCores: " << check.nPhysicalCores << "\n";
    cout << "CPU nLogicalCores: " << check.nLogicalCores << "\n";
    cout << "CPU currentClockSpeed: " << check.currentClockSpeed << "\n";
    cout << "CPU maxClockSpeed: " << check.maxClockSpeed << "\n";
    cout << "CPU cacheSize: " << check.cacheSize << "\n";
    cout << "-----------------------------------------------\n";
    cout << "Press Enter to end program...";
    std::cin.ignore();
    return 0;
}