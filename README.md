# Hardware info
#### Video Demo:  <URL https://youtu.be/SpXE1cokv9Y>

Hardware info is project written in C++ via WMI and CMake.To query hardware info about user computer and output in simple comand line interface. Here is sections of information:

> [!NOTE]
> The WMI Diagnosis Utility ( WMIDiag.exe ) is no longer supported, starting with Windows 8 and Windows Server 2012. Windows 7, Windows Server 2008 R2, Windows Vista and Windows Server 2008: If WMI returns error messages, be aware that they might not indicate problems in the WMI service or in WMI providers.

1. Base board
    - Model
    - Manufacturer
    - Serial Number
    - Driver version

2. CPU
    - Model
    - Manufacturer
    - Physical cores
    - Logical cores
    - Current clock speed
    - Max clock speed
    - Chache size

3. Disk
    - Device ID
    - Model
    - Size
    - Bus type
    - Media type

    - Partions (Drives)
        - Volume
        - Total space
        - Free space
        - File system

4. GPU
    - Model
    - Manufacturer
    - Memory amount
    - Driver version
    - Refresh rate
    - Resolution

5. OS
    - Name
    - Architecture
    - Serial number
    - Desktop name

6. RAM
    - Model
    - Manufacturer
    - Capacity
    - Speed
    - Serial number

## Aditional fetuares
#### Program also provides built-in help menu and fetuare to save outputed information into txt file.
> [!NOTE]
> If program not opened with administrator rights files will be saved only in scope of current user file system.

## Files
Files containes 2 directories .gitignore and CMakeLists.txt files. CMakeLists.txt need to proper usage of CMake, while .gitignore for proper usage of git.

### Directories
- src: Source directory contains main cpp while that create console window and invoke functions.
- include: Contains 2 directories that implements program work
    - hardware: directory contains header files that queries and processes returned info.
    - utils: header files that contains services to create logic of program:
        - InitWMI.h: file that start WMI service and returns processed info.
        - menus.h: file contains all menus that outputs userInteraction.h.
        - userInteraction.h: creates interface that user work with.

## Build
Program compiles only with Microsoft visual studio compiler (MVSC). To build project use visual studio or CMake with Visual Studio generator.

## Troubleshooting
Errors outputs next to input. 
### Wrong input, write Help to get instructions
Basic problem, that error outputed when user gives wrong.
Its may be: digits bigger that 9 or smaller that 0, arguments bigger that 5 length, characters that are not in the encoding "Code Page 850" (cmd encoding) and etc.

### Can't save file by specified PATH
Path writen with "." or ".." like "../../FolderToSaves" or ".". Program not opened with administrator rigths and path out of user scope, like "C:\". Also usage "/" instead of "\\" may create error.

## Disclaimer

Please note that the code in this repository may contain mistakes or suboptimal implementations. I am still learning and would greatly appreciate any feedback or suggestions for improvement.

### How to Contribute

I would love to hear your thoughts and suggestions! If you find any issues or have any advice on how to improve the code, please feel free to:

- Open an issue
- Submit a pull request
- Leave comments

### Contact

If you want to reach out to me directly, you can contact me on reddit: u/Aranosy1.

Thank you for taking the time to review my project. Your feedback is invaluable to my learning process!
