#include "rma.h"
#include <exception>

using namespace std;

RMA::RMA()
{
}

string lower(string s)
{
        for (auto itr = s.begin(); itr != s.end(); ++itr) {
                *itr = tolower(*itr);
        }
        return s;
}
inline void RMA::proc_loc(Info &nf, const string &tmp, int qty)
{
        if (tmp == "rtv") {
                nf.m_rtv += qty;
        } else if (tmp == "elm") {
                nf.m_elm += qty;
        }
}
/*
 *
 *
 *
 */
void RMA::add()
{
        string rma_nm = Tokenizer::get_token();
        string pn = Tokenizer::get_token();
        string mdl = Tokenizer::get_token();
        int qty = stoi(Tokenizer::get_token());
        string loc = Tokenizer::get_token();
        string tmp(lower(loc));
        Info nf(pn, mdl);
        proc_loc(nf, tmp);
        /*
         * replaced by proc_loc
        if (tmp == "rtv") {
                nf.m_rtv = qty;
        } else if (tmp == "elm") {
                nf.m_elm = qty;
        }
        */
        if (m_info.find(rma_nm) == m_info.end()) {
                m_info[rma_nm].push_back(nf);
        } else {
                auto &vt = m_info.at(rma_nm);
                for (auto itr = vt.begin(); itr != vt.end(); ++itr) {
                        if (itr->m_pn == pn) {
                                proc_loc(*itr, tmp, qty);
                                /*
                                 * replace by proc_loc()
                                if (tmp == "rtv") {
                                        itr->m_rtv += qty;
                                } else if (tmp == "elm") {
                                        itr->m_elm += qty;
                                }
                                */
                                return;
                        }
                }
                m_info[rma_nm].push_back(nf);
                cout << m_info.size();
        }
}

void RMA::print(ostream &cout, const std::string &s) const
{
        for (auto itr = this->m_info.begin();
             itr != this->m_info.end();
             ++itr) {
                for (auto iitr = itr->second.begin();
                     iitr != itr->second.end();
                     ++iitr) {
                        cout << s << '\t' << itr->first << '\t' << *iitr;
                        cout << endl;
                }
        }
}
ostream& operator<<(ostream &cout, const RMA &rma)
{
        for (auto itr = rma.m_info.begin(); itr != rma.m_info.end(); ++itr) {
                for (auto iitr = itr->second.begin();
                     iitr != itr->second.end();
                     ++iitr) {
                        cout << itr->first << '\t' << *iitr << endl;
                }
        }
        return cout;

}

void RMA::do_PN_substitude()
{

}

void RMA::RMA_qty_calc()
{
        for (auto itr = rma.m_info.begin(); itr != rma.m_info.end(); ++itr) {
                for (auto iitr = itr->second.begin();
                     iitr != itr->second.end();
                     ++iitr) {
                        iitr->xtr_qty = m_elm - m_rtv + m_sub_tot;
                }
        }
        return cout;

}
