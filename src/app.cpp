#include <userInteraction.h>
using namespace hardware;
using namespace WMI;

void BindStdHandlesToConsole()
{
    //TODO: Add Error checking.
    
    // Redirect the CRT standard input, output, and error handles to the console
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stderr);
    freopen("CONOUT$", "w", stdout);
    
    // Note that there is no CONERR$ file
    HANDLE hStdout = CreateFile("CONOUT$",  GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hStdin = CreateFile("CONIN$",  GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    SetStdHandle(STD_OUTPUT_HANDLE,hStdout);
    SetStdHandle(STD_ERROR_HANDLE,hStdout);
    SetStdHandle(STD_INPUT_HANDLE,hStdin);

    //Clear the error state for each of the C++ standard stream objects. 
    std::wclog.clear();
    std::clog.clear();
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();
}


int WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR lpCmdLine,
            int nCmdShow)
{
    AllocConsole();
    SetConsoleTitle("Hardware info V2");
    BindStdHandlesToConsole();
    CONSOLE_SCREEN_BUFFER_INFOEX consolesize;

    consolesize.cbSize = sizeof(consolesize);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfoEx(hConsole, &consolesize);

    COORD c;
    c.X = 115;
    c.Y = 23;
    consolesize.dwSize = c;

    consolesize.srWindow.Left = 100;
    consolesize.srWindow.Right = 700;
    consolesize.srWindow.Top = 0;
    consolesize.srWindow.Bottom = 50;

    SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
    setlocale(LC_ALL, "en_US.UTF-8");
    Console::Start();
    cin.ignore();
}