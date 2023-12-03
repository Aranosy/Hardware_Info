#pragma once

#include "../hardware/hardware.h"
#include "menus.h"
#include <typeinfo>
using namespace hardware;

vector<string> commands{"base_board", "cpu", "disk", "gpu", "os", "ram"};
short page = 2;
string input = "";

namespace Console
{

    void GotoXY(int x, int y)
    {
        COORD pos = {x, y};
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(output, pos);
    }

    void HandleInput();

    void OutputConst()
    {
        // Output program name
        cout << "\xC9";
        for (int i = 0; i < 112; i++)
            cout << "\xCD";
        cout << "\xBB\n";
        cout << "\xBA";
        for (int i = 0; i < 85; i++)
            if (i == 45)
                cout << "Hardware info";
            else
                cout << " ";
        cout << "Version 2.0.0.0"
             << "\xBA\n";

        cout << "\xC8";
        for (int i = 0; i < 112; i++)
            cout << "\xCD";
        cout << "\xBC\n";

        // Open big table
        cout << "\xC9";
        for (int i = 0; i < 112; i++)
            cout << "\xCD";
        cout << "\xBB\n";

        cout << "\xBA";
        cout << "\xC9";
        for (int i = 0; i < 20; i++)
            cout << "\xCD";
        cout << "\xBB";

        cout << "\xC9";
        for (int i = 0; i < 88; i++)
            cout << "\xCD";
        cout << "\xBB";
        cout << "\xBA\n";

        // Output middle of table
        for (int line = 0; line < 12; line++)
        {
            cout << "\xBA";
            cout << "\xBA";

            for (int i = 0; i < 20; i++)
                cout << " ";

            cout << "\xBA";
            cout << "\xBA";

            for (int i = 0; i < 88; i++)
                cout << " ";

            cout << "\xBA";
            cout << "\xBA\n";
        }

        // Close big table
        cout << "\xBA";
        cout << "\xC8";
        for (int i = 0; i < 20; i++)
            cout << "\xCD";
        cout << "\xBC";

        cout << "\xC8";
        for (int i = 0; i < 88; i++)
            cout << "\xCD";
        cout << "\xBC";
        cout << "\xBA\n";

        cout << "\xC8";
        for (int i = 0; i < 112; i++)
            cout << "\xCD";
        cout << "\xBC\n";

        // Output input table
        cout << "\xC9";
        for (int i = 0; i < 112; i++)
            cout << "\xCD";
        cout << "\xBB\n";

        cout << "\xBA";
        cout << " >";
        for (int i = 0; i < 110; i++)
            cout << " ";
        cout << "\xBA\n";

        cout << "\xC8";
        for (int i = 0; i < 112; i++)
            cout << "\xCD";
        cout << "\xBC\n";
    }

    void OutputMenu(vector<linkMenu> m, vector<string> info, string name)
    {
        short mPoint = (m.size() <= 7) ? 0 : +((page - 1) * 7);
        short iPoint = (info.size() <= 7) ? 1 : 1 + ((page - 1) * 7);
        short line = 0;
        // Menu and info names
        GotoXY((20 - name.length()) / 2 + 2, 6);
        cout << name;
        GotoXY((88 - info[0].size()) / 2 + 24, 6);
        cout << info[0];

        while (mPoint < m.size() && mPoint < page * 7)
        {
            GotoXY(3, line + 8);
            cout << mPoint + 1 << " " << m[mPoint].point;
            mPoint++;
            line++;
        }

        line = 0;

        while (iPoint < info.size() && iPoint <= page * 7)
        {
            GotoXY(24, line + 8);
            cout << " " << info[iPoint];
            iPoint++;
            line++;
        }
        GotoXY(4, 20);
    }


    // void OutputLinkMenu(linkMenu m, vector<string> info, string name, bool check = false)
    // {
    //     if (check)
    //     {
    //         vector<vector<outMenu>> nextVM = m.next_menus;
    //         short mPoint = (nextVM[0].size() <= 7) ? 0 : +((page - 1) * 7);
    //     }
    //     else
    //     {
    //         vector<outMenu> nextM = m.next_menus;
    //         short mPoint = (nextM.size() <= 7) ? 0 : +((page - 1) * 7);
    //     }
    //     short iPoint = (info.size() <= 7) ? 1 : 1 + ((page - 1) * 7);
    //     short line = 0;
    //     // Menu and info names
    //     GotoXY((20 - name.length()) / 2 + 2, 6);
    //     cout << name;
    //     GotoXY((88 - info[0].size()) / 2 + 24, 6);
    //     cout << info[0];

    //     while (mPoint < m.size() && mPoint < page * 7)
    //     {
    //         GotoXY(3, line + 8);
    //         cout << mPoint + 1 << " " << m[mPoint].point;
    //         mPoint++;
    //         line++;
    //     }

    //     line = 0;

    //     while (iPoint < info.size() && iPoint <= page * 7)
    //     {
    //         GotoXY(24, line + 8);
    //         cout << " " << info[iPoint];
    //         iPoint++;
    //         line++;
    //     }
    //     GotoXY(4, 20);
    // }

    void Start()
    {
        OutputConst();
        OutputMenu(start_links, start_info, "MENU");
    }

};