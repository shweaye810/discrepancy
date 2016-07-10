#include <sstream>

#include "asp.h"

using namespace std;

ASP::ASP()
{
}

void ASP::add(string s)
{
        Tokenizer::set_string(s);
        string asp_nm = Tokenizer::get_token();
        if (m_row.find(asp_nm) == m_row.end()) {
                RMA rma;
                rma.add();
                m_row[asp_nm] = rma;
        } else {
                RMA &tmp_rma = m_row[asp_nm];
                tmp_rma.add();
        }
}

ostream& operator<<(ostream &cout, const ASP &asp)
{
        for (auto itr = asp.m_row.begin(); itr != asp.m_row.end(); ++itr) {
                /*for (auto iitr = itr->second.begin();
                     iitr != itr->second.end();
                     ++iitr) {
                        cout << itr->first << '\t' << *iitr << endl;
                        }*/
                //cout << itr->first << '\t' << itr->second;
                itr->second.print(cout, itr->first);
        }
        return cout;
}

void ASP::calc_qty()
{
        for (auto itr = m_row.begin(); itr != m_row.end(); ++itr) {
                itr->second.calc_qty();
        }
}

void ASP::substitude_PN()
{
        for (auto itr = m_row.begin(); itr != m_row.end(); ++itr) {
                itr->second.substitude_PN();
        }
}
