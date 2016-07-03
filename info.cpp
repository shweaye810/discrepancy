#include <cctype>

#include "info.h"

using namespace std;

#define TAB '\t'

Info::Info(string part_n, string model, int qty, string loc) :
        m_pn(part_n), m_mdl(model), m_qty(qty), m_loc(loc)
{
}

Info::Info(const Info &o) : m_pn(o.m_pn), m_mdl(o.m_mdl)
{

}

string lower(string s)
{
        for (auto itr = s.begin(); itr != s.end(); ++itr) {
                s = tolower(*itr);
        }
        return s;
}

ostream& operator<<(ostream &cout, const Info &info)
{

        cout << info.m_pn << '\t' << info.m_mdl << '\t';
        if (lower(info.m_loc) == "rtv") {
                cout << 0 << '\t' << info.m_qty << '\t';
        } else if (lower(info.m_loc) == "elm") {
                cout << info.m_qty << '\t' << 0 << '\t';
        }
        cout << info.xtr_qty << '\t' <<
                info.sb_tot_qty <<  '\t';
        return cout;
}
