#include <hardware/InitWMI.h>

int main(void)
{
    std::vector<const wchar_t*> vendors{};
    hardware::WMIExec("Win32_Processor", "Name", vendors);
    std::vector<std::string> ret;
    ret.reserve(vendors.size());
    for (auto& v : vendors) {
        if (v == nullptr) {
        continue;
        }
        std::wstring tmp(v);
        ret.emplace_back(tmp.begin(), tmp.end());
    }

    for(auto i: ret)
    {
        cout << i;
    }

  return 0;
}