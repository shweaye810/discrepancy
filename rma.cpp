#include <cstdlib>
#include <exception>

#include "rma.h"

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

inline int get_qty(const Info &l, const Info &r)
{
        return abs(l.extra_qty()) < r.extra_qty() ?
                                    abs(l.extra_qty()) : r.extra_qty();
}
void RMA::full_PN_substitude()
{
        for (auto i = m_info.begin(); i != m_info.end(); i++) {
                for (auto j = i->second.begin(); j != i->second.end(); j++) {
                        if (j->is_done() || j->xtr_qty >= 0) {
                                continue;
                        }
                        for (auto k = i->second.begin(); k != i->second.end(); k++) {
                                if (k->is_done()) {
                                        continue;
                                }
                                if ((j != k && k->xtr_qty > 0) &&
                                    (j->m_mdl.find(k->m_mdl) != string::npos ||
                                     k->m_mdl.find(j->m_mdl) != string::npos)) {
                                        //int qty = abs(j->xtr_qty) < k->xtr_qty ? abs(j->xtr_qty) : k->xtr_qty;
                                        int qty = get_qty(*j, *k);
                                        j->m_sub[k->m_pn] = qty;
                                        j->m_sub_tot += qty;
                                        k->m_sub_tot -= qty;
                                        j->calc_qty();
                                        k->calc_qty();
                                        if (j->is_done())
                                                break;
                                }
                        }
                }
        }
}

void RMA::substitude_PN()
{
        full_PN_substitude();
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
        proc_loc(nf, tmp, qty);
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
                //cout << m_info.size();
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

void RMA::calc_qty()
{
        for (auto itr = m_info.begin(); itr != m_info.end(); ++itr) {
                for (auto iitr = itr->second.begin();
                     iitr != itr->second.end();
                     ++iitr) {
                        iitr->calc_qty();
                }
        }
}
