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
        GotoXY(4, 20);
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

    void OutputStartMenu(vector<linkMenu> m, vector<string> info, string name = "MENU")
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
        pages = {};
        vector<vector<string>> pagesT;
        vector<string> temp;
        for (linkMenu i : m)
        {
            if (temp.size() == 10)
            {
                pagesT.push_back(temp);
                temp = {};
            }
            string p = "";
            for (int t = 0; t < (87 - i.point.size()) / 2; t++)
                p += " ";
            p += i.point;
            temp.push_back(p);
            temp.push_back("");

            for (string s : i.info)
            {
                if (temp.size() >= 10)
                {
                    pagesT.push_back(temp);
                    temp = {};
                }
                temp.push_back(s);
            }
        }
        if (temp.size() >= 10)
        {
            while (temp.size() < 10)
                temp.push_back("");
            pagesT.push_back(temp);
        }
        short enpage = 1;
        for (int i = 0; i < pagesT.size(); i++)
        {
            string pagesS = "Page<" + to_string(enpage) + "," + to_string(pagesT.size()) + ">";
            string strPages = "";
            for (int i = 0; i < 87 - pagesS.length() - 1; i++)
            {
                strPages += " ";
            }
            strPages += pagesS;
            pagesT[i].push_back(strPages);
            enpage++;
        }

        pages = pagesT;
        nPage = pages.size();
    }

    void OutputMenu(vector<string> m)
    {
        GotoXY(10, 6);
        cout << "MENU";
        GotoXY(3, 8);
        cout << "1 BACK";

        short line = 0;
        for (string i : m)
        {
            GotoXY(24, line + 6);
            cout << " " << i;
            line++;
        }
    }

    void Start()
    {
        SetPages(start_links);
        while (true)
        {
            HandleInput();
            OutputConst();
            OutputMenu(pages[page]);
        }
        cin.ignore();
    }

};