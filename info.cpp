#include <cctype>

#include "info.h"

using namespace std;

Info::Info(string part_n, string model) :
        m_pn(part_n), m_mdl(model), m_elm(0), m_rtv(0), xtr_qty(0), m_sub_tot(0)
{

}


Info::Info(const Info &o) : m_pn(o.m_pn), m_mdl(o.m_mdl),
                            m_elm(o.m_elm), m_rtv(o.m_rtv), xtr_qty(o.xtr_qty),
                            m_sub_tot(o.m_sub_tot), m_sub(o.m_sub)
{
}

ostream& operator<<(ostream &cout, const Info &info)
{
        cout << info.m_pn << '\t' << info.m_mdl << '\t' << info.m_elm << '\t'
             << info.m_rtv << '\t'<< info.xtr_qty << '\t' << m_sub_tot << '\t';

        for (auto itr = info.m_sub.begin(); itr != info.m_sub.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\t';
        }

        return cout;
}
