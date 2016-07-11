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
             << info.m_rtv << '\t'<< info.xtr_qty << '\t'
             << info.m_sub_tot << '\t';

        for (auto itr = info.m_sub.begin(); itr != info.m_sub.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\t';
        }

        return cout;
}

bool Info::is_done()
{
    return xtr_qty == 0;
}

void Info::calc_qty()
{
    xtr_qty = m_elm - m_rtv + m_sub_tot;
}

int Info::extra_qty() const
{
    return xtr_qty;
}

bool Info::is_HDD() const
{
    return m_mdl.find("SATA") != string::npos &&
        m_mdl.find("SSD") == string::npos;
}

bool Info::is_MB() const
{
    return m_mdl.find("MB") != string::npos ||
        m_mdl.find("MAIN_BD") != string::npos;
}

bool Info::is_battery() const
{
    return m_mdl.find("BATT") != string::npos;
}

bool Info::is_adapter() const
{
    return m_mdl.find("ADAPTER") != string::npos;
}


int get_qty(const Info &l, const Info &r)
{
    return abs(l.extra_qty()) < r.extra_qty() ?
                                abs(l.extra_qty()) : r.extra_qty();
}

bool Info::has_extra()
{
    return xtr_qty > 0;
}

void Info::substitude_PN(Info &o)
{
    int qty = get_qty(*this, o);
    this->m_sub[o.m_pn] = qty;
    this->m_sub_tot += qty;
    o.m_sub_tot -= qty;
    this->calc_qty();
    o.calc_qty();
}

const string &Info::model() const
{
    return m_mdl;
}
