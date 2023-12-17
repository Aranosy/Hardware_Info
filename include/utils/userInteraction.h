#pragma once

#include "../hardware/hardware.h"
#include "menus.h"
#include <typeinfo>
using namespace hardware;

vector<string> commands{"base_board", "cpu", "disk", "gpu", "os", "ram"};
short page = 0;
short nPage = 0;
short mPoint = 0;
short curLinkM = 0;
string input = "";
vector<vector<string>> pages = {};
vector<outMenu> outputO = {};
vector<linkMenu> outputL = {};

namespace Console
{

    void GotoXY(int x, int y)
    {
        COORD pos = {x, y};
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(output, pos);
    }

    void HandleInput()
    {
        getline(cin, input);

        if (input == "N" && page != nPage - 1)
            page++;
        else if (page > 0 && input == "B")
        {
            page--;
            mPoint -= 8;
        }
    }

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

    void OutputMenu(vector<linkMenu> m, vector<string> info, string name = "MENU")
    {
        nPage = 2;
        mPoint = (m.size() <= 8) ? 0 : ((page) * 8);
        short iPoint = (info.size() <= 8) ? 1 : 1 + ((page) * 8);
        short line = 0;
        // Menu and info names
        GotoXY((20 - name.length()) / 2 + 2, 6);
        cout << name;
        GotoXY((88 - info[0].size()) / 2 + 24, 6);
        cout << info[0];

        while (mPoint < m.size() && mPoint < (page + 1) * 8)
        {
            GotoXY(3, line + 8);
            cout << mPoint + 1 << " " << m[mPoint].point;
            outputL.push_back(m[mPoint]);
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

    void SetPages(vector<linkMenu> m)
    {
        short line = 0;
        mPoint = 0;
        vector<outMenu> out = {};

        for (linkMenu menu : m)
        {
            for (outMenu i : menu.next_menus)
            {
                out.push_back(i);
            }
        }

        outputO = out;
        out = {};

        vector<short> chapters = {0};

        for (int i = 0; i < m.size() - 1; i++)
        {
            chapters.push_back(chapters[i] + m[i].next_menus.size());
        }

        int sum = 0;
        for (auto i : m)
            sum += 3 + i.next_menus.size();
        short nPages = floor(sum / 8);
        for (int i = 0; i < nPages; i++)
        {
            pages.push_back({});
        }

        short enpage = 1;
        for (int i = 0; i < pages.size(); i++)
        {
            vector<string> strTemp = {};
            int temp = 1;
            strTemp.push_back(" ");
            if (mPoint == 0)
            {
                string p = "";
                for (int i = 0; i < (20 - m[curLinkM].point.length()) / 2 - 1; i++)
                {
                    p += " ";
                }
                p += m[curLinkM].point;
                strTemp.push_back(p);
                strTemp.push_back(" ");
                line += 2;
            }
            while (mPoint < outputO.size() && line != 9)
            {
                if (mPoint == chapters[temp])
                {
                    string p = "";
                    strTemp.push_back(" ");
                    for (int i = 0; i < (20 - m[temp].point.length()) / 2 - 1; i++)
                    {
                        p += " ";
                    }
                    p += m[temp].point;
                    strTemp.push_back(p);
                    strTemp.push_back(" ");
                    line += 2;
                    temp++;
                }

                string point = to_string(mPoint + 1) + " " + outputO[mPoint].point;
                strTemp.push_back(point);
                mPoint++;
                line++;
            }
            line = 0;
            string pagesS = "Page<" + to_string(enpage) + "," + to_string(pages.size()) + ">";
            string strPages = "";
            for (int i = 0; i < 20 - pagesS.length() - 1; i++)
            {
                strPages += " ";
            }
            strPages += pagesS;
            strTemp.push_back(strPages);
            pages[i] = strTemp;
            enpage++;
        }
    }

    void OutputLinkMenu(vector<string> menu, vector<string> info)
    {
        short iPoint = 1;
        short line = 0;

        for (int i = 0; i < menu.size(); i++)
        {
            if (i == menu.size() - 1)
            {
                GotoXY(3, 16);
                cout << menu[i];
            }
            else
            {
                GotoXY(3, line + 5);
                cout << menu[i];
                line++;
            }
        }

        line = 0;

        GotoXY((88 - info[0].size()) / 2 + 24, 6);
        cout << info[0];

        while (iPoint < info.size() && iPoint <= page * 8)
        {
            GotoXY(24, line + 8);
            cout << " " << info[iPoint];
            iPoint++;
            line++;
        }

        GotoXY(4, 20);
    }

    void Start()
    {
        OutputConst();
        OutputMenu(start_links, start_info);
        HandleInput();
        OutputConst();
        OutputMenu(start_links, start_info);
        HandleInput();
        SetPages({baseBoardM, cpuM});
        OutputConst();
        OutputLinkMenu(pages[page], start_info);
        HandleInput();
        OutputConst();
        OutputLinkMenu(pages[page], start_info);
        HandleInput();
        OutputConst();
        OutputLinkMenu(pages[page], start_info);

        cin.ignore();
    }

};