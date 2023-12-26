#include "menus.h"
#include <fstream>
#include <typeinfo>
using namespace hardware;

short page = 0;
short nPage = 0;
bool inMenu = false;
vector<vector<string>> pages = {};
vector<linkMenu> output = {};
vector<linkMenu> outputO = {};
vector<string> par = {"PATH", "HELP", "NEXT", "PAST"};
bool isSaved = false;
int inputLength = 4;

namespace Console
{

    void OutError(string s);

    void GotoXY(int x, int y)
    {
        COORD pos = {x, y};
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(output, pos);
    }

    bool is_number(const string &s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it))
            ++it;
        return !s.empty() && it == s.end();
    }

    vector<string> split(const string &s, char sep)
    {
        vector<string> ret;
        string temp = s;
        short i = 0;
        temp += " ";
        while (i < temp.size())
        {
            if (temp[i] == sep && temp[i + 1] != sep)
            {
                ret.push_back(temp.substr(0, i));
                temp.erase(0, i + 1);
                i = 0;
            }
            else
                i++;
        }
        return ret;
    }

    string toupper_str(const string &s)
    {
        string ret;
        for (char i : s)
            ret += toupper(i);

        return ret;
    }

    void OutputConst()
    {
        GotoXY(0, 0);
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
        cout << "Version 1.0.0.0"
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

    void SetStartMenu(vector<menu> m)
    {
        vector<vector<string>> r = {};
        vector<string> ret = {};
        short en = 1;
        for (auto i : m)
        {
            if (ret.size() < 9)
            {
                ret.push_back(" ");
                string n = "";
                for (int s = 0; s < (20 - i.name.length()) / 2; s++)
                    n += " ";
                ret.push_back(n + i.name);
                ret.push_back(" ");
            }
            else
            {
                r.push_back(ret);
                ret = {};
                ret.push_back(" ");
                string n = "";
                for (int s = 0; s < (20 - i.name.length()) / 2; s++)
                    n += " ";
                ret.push_back(n + i.name);
                ret.push_back(" ");
            }
            for (auto p : i.links)
            {
                if (ret.size() < 9)
                {
                    ret.push_back(" " + to_string(en) + " " + p.point);
                    output.push_back(p);
                    en++;
                }
                else
                {
                    r.push_back(ret);
                    ret = {};
                }
            }
        }

        if (!ret.empty())
            r.push_back(ret);

        for (int i = 0; i < r.size(); i++)
        {
            while (r[i].size() < 11)
                r[i].push_back(" ");
            string strP;
            for (int i = 0; i < 9; i++)
                strP += " ";

            r[i].push_back(strP + "Page<" + to_string(i + 1) + ",2> ");
        }
        pages = r;
        nPage = 2;
    }

    void OutputStartMenu(vector<string> m, vector<string> info)
    {
        short line = 0;
        short iPoint = 1;
        // Menu and info names
        for (auto i : m)
        {
            GotoXY(3, line + 5);
            cout << i;
            line++;
        }

        line = 0;
        GotoXY((88 - info[0].size()) / 2 + 24, 6);
        cout << info[0];

        while (iPoint < info.size() && iPoint <= page + 1 * 12)
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
            if (temp.size() > 8)
            {
                pagesT.push_back(temp);
                temp = {};
            }
            string p = "";
            for (int t = 0; t < (87 - i.point.size()) / 2; t++)
                p += " ";
            p += i.point;
            temp.push_back("");
            temp.push_back(p);
            temp.push_back("");

            for (string s : i.info)
            {
                if (temp.size() >= 11)
                {
                    pagesT.push_back(temp);
                    temp = {};
                }
                temp.push_back(s);
            }
        }
        if (temp.size() < 11)
        {
            while (temp.size() < 11)
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
        GotoXY(3, 9);
        cout << "2 SAVE TO LOG";

        short line = 0;
        for (string i : m)
        {
            GotoXY(24, line + 5);
            cout << " " << i;
            line++;
        }
    }

    void SaveLog(string path = "")
    {
        string p;
        if (path != "")
            p += path + "\\log.txt";
        else
            p = "log.txt";
        
        ofstream log_file(p);

        if (!log_file)
            OutError("Can't save file by specified PATH");
        for (vector<string> p: pages)
            for (int i = 0;i < p.size() - 1; i++)
                log_file << p[i] << endl;
        isSaved = true;
        nPage = 1;
        if (path == "")
             pages = {{"Created file named log.txt in program directory."}};
        else
            pages = {{"Created file by path " + path + ""}};

    }

    void HandleInput()
    {
        string input = "";
        GotoXY(inputLength, 20);
        getline(cin, input);
        inputLength = 4;

        if (input.length() == 0)
        {
            if (inMenu)
            {
                SetPages(outputO);
                OutputConst();
                OutputMenu(pages[page]);
            }
            else
            {
                OutputConst();
                OutputStartMenu(pages[page], start_info);
            }
            HandleInput();
        }

        vector<string> sep = split(input, ' ');
        if (inMenu == true && sep.size() > 1)
            if (sep[0] == "2")
            {
                sep = split(input, '"');
                if (sep.empty())
                    OutError("Can't save file by specified PATH");

            }
            else
                OutError("Wrong input, write Help to get instructions");

        

        for (string i : sep)
            if (i.length() >= 5 && sep[0] != "2 ")
                OutError("Wrong input, write Help to get instructions");

        short bounds = (inMenu == false) ? 10 : 3;
        short inB = 0;
        for (string i : sep)
            if (is_number(i))
            {
                int n = stoi(i);
                if (n < bounds && n > 0)
                    inB++;
            }

        if (inB == sep.size())
            outputO = {};

        for (string i : sep)
        {
            if (toupper_str(i) == "HELP")
            {
                outputO = {output[6]};
                break;
            }
            else if (toupper_str(i) == "NEXT")
            {
                if (page != nPage - 1)
                    page++;
                break;
            }
            else if (toupper_str(i) == "PAST")
            {
                if (page > 0)
                    page--;
                break;
            }
            else if (is_number(i) && inMenu == false)
            {
                int n = stoi(i) - 1;
                if (n == 6)
                {
                    outputO = {output[n]};
                    break;
                }
                else if (n == 7)
                {
                    outputO = start_links[0].links;
                    break;
                }
                else if (n == 8)
                    exit(0);
                else if (n < 6 && n > -1)
                    outputO.push_back(output[n]);
                else
                    OutError("Wrong input, write Help to get instructions");
            }
            else if ((is_number(i) && inMenu == true) || sep[0] == "2 ")
            {
                if (i == "1")
                {
                    outputO = {};
                    inMenu = false;
                    page = 0;
                    SetStartMenu(start_links);
                }
                else if (sep.size() == 2 || i == "2")
                {
                    if (isSaved)
                        OutError("File already saved");
                    if (sep.size() == 2)
                        SaveLog(sep[1]);
                    else
                        SaveLog();
                    OutputConst();
                    OutputMenu(pages[0]);
                    HandleInput();
                }
            }
            else
                OutError("Wrong input, write Help to get instructions");
        }

        isSaved = false;

        if (!outputO.empty())
        {
            if (inMenu == false)
                page = 0;
            inMenu = true;
            SetPages(outputO);
            OutputConst();
            OutputMenu(pages[page]);
        }
        else
        {
            OutputConst();
            OutputStartMenu(pages[page], start_info);
        }
        // ...
        HandleInput();
    }

    void OutError(string s)
    {
        if (!outputO.empty())
        {
            SetPages(outputO);
            OutputConst();
            OutputMenu(pages[page]);
        }
        else if (isSaved)
        {
            OutputConst();
            OutputMenu(pages[0]);
        }
        else
        {
            OutputConst();
            OutputStartMenu(pages[page], start_info);
        }

        GotoXY(2, 20);
        s += " > ";
        inputLength = s.size() + 2;
        cout << s;
        HandleInput();
    }

    void Start()
    {
        OutputConst();
        SetStartMenu(start_links);
        OutputStartMenu(pages[0], start_info);
        HandleInput();
        cin.ignore();
    }

};