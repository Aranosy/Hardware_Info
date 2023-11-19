#pragma once

#include "../hardware/hardware.h"

using namespace hardware;

namespace Console
{
    vector<string> commands{"base_board", "cpu", "disk", "gpu", "os", "ram"};

    string input = "";

    void HandleInput();

    void DisplayBB()
    {
        BaseBoard baseBoard;
        cout << "Model: " << baseBoard.name << "\n";
        cout << "Manufacturer: " << baseBoard.vendor << "\n";
        cout << "Driver version: " << baseBoard.version << "\n";
        cout << "Serial number: " << baseBoard.serialN << "\n";
        HandleInput();
    }

    void DisplayCPU()
    {
        CPU check;
        cout << "Model: " << check.model << "\n";
        cout << "Manufacturer: " << check.vendor << "\n";
        cout << "Physical cores: " << check.nPhysicalCores << "\n";
        cout << "Logical cores: " << check.nLogicalCores << "\n";
        cout << "Current clock speed: " << check.currentClockSpeed << "\n";
        cout << "Max clock speed: " << check.maxClockSpeed << "\n";
        cout << "Cache size: " << check.cacheSize << "\n";
        HandleInput();
    }

    void DisplayDisk()
    {
        Drives disks;
        for (auto i : disks.disks)
        {
            cout << "Drive: " << i.deviceID << "\n";
            cout << "Bus type: " << i.busType << "\n";
            cout << "Model: " <<i.model << "\n";
            cout << "Media type: " <<i.mediaType << "\n";
            cout << "Serial number: " <<i.serialN << "\n";
            cout << "Size: " <<i.size << "GB"
                 << "\n";
            for (auto p : i.partions)
            {
                cout << "Partion: \"" << p.volume << "\"\n";
                cout << "Total space: " << p.totalSpace << "\n";
                cout << "Free space: " << p.freeSpace << "\n";
                cout << "File system: " << p.fileSystem << "\n";
            }
        }
        HandleInput();
    }

    void DisplayGPU()
    {
        GPU gpu;
        for (size_t i = 0; i < gpu.model.size(); i++)
        {
            cout << "Model: " << gpu.model[i] << "\n";
            cout << "Mendor: " << gpu.vendor[i] << "\n";
            cout << "Memory amount: " << gpu.memoryAmount[i] << "\n";
            cout << "Driver version: " << gpu.driverVersion[i] << "\n";
        }
        HandleInput();
    }

    void DisplayOS()
    {
        OS os;
        cout << "Operating Sytem: " << os.os << "\n";
        cout << "Name: " << os.name << "\n";
        cout << "Architecture: " << os.architecture << "\n";
        cout << "Serial number: " << os.serialN << "\n";
        HandleInput();
    }

    void DisplayRAM()
    {   
        RAM ram;
        cout << "Serial number: " << ram.serialN << "\n";
        cout << "Model: " << ram.model << "\n";
        cout << "Size: " << ram.size << "\n";
        cout << "Manufacturer: " << ram.vendor << "\n";
        cout << "Speed: " << ram.speed << "\n";
        HandleInput();
    }

    void HandleInput()
    {
        cout << ">";
        getline(cin, input);

        int cmd = 0;
        for (int i = 0; i < commands.size(); i++)
            if (input == commands[i])
            {
                cmd = i + 1;
                break;
            }
        switch (cmd)
        {
        case 1:
            DisplayBB();
            break;
        case 2:
            DisplayCPU();
            break;
        case 3:
            DisplayDisk();
            break;
        case 4:
            DisplayGPU();
            break;
        case 5:
            DisplayOS();
            break;
        case 6:
            DisplayRAM();
            break;
        default:
            cout << "Error!\n";
            HandleInput();
        }
    }

    void Create()
    {
        cout << "Hello! Version 1.0.0.0!\n";
        HandleInput();
    }

};