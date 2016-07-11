#include <cstdlib>
#include <exception>
#include <vector>

#include "rma.h"
#include "product.h"

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

void RMA::substitude_full_PN()
{
        for (auto i = m_info.begin(); i != m_info.end(); i++) {
                for (auto j = i->second.begin(); j != i->second.end(); j++) {
                        if (j->is_done() || j->xtr_qty >= 0)
                                continue;
                        for (auto k = i->second.begin(); k != i->second.end();
                             k++) {
                                if (k->is_done()) {
                                        continue;
                                }
                                if ((j != k && k->xtr_qty > 0) &&
                                    (j->m_mdl.find(k->m_mdl) != string::npos ||
                                     k->m_mdl.find(j->m_mdl) != string::npos)) {
                                        j->substitude_PN(*k);
                                        /*
                                         * replace by substidude_PN(Info &)
                                        int qty = get_qty(*j, *k);
                                        j->m_sub[k->m_pn] = qty;
                                        j->m_sub_tot += qty;
                                        k->m_sub_tot -= qty;
                                        j->calc_qty();
                                        k->calc_qty();
                                        */
                                        if (j->is_done())
                                                break;
                                }
                        }
                }
        }
}

template<typename T>
string get_hdd(const Info &o, const T &tmp)
{
        for (auto &i : tmp) {
                if (o.model().find(i) != string::npos)
                        return i;
        }
        return "";
}

void RMA::substitude_HDD()
{
        for (auto i = m_info.begin(); i != m_info.end(); i++) {
                for (auto j = i->second.begin(); j != i->second.end(); j++) {
                        if (j->is_done() || !j->is_HDD()|| j->has_extra())
                                continue;
                        for (auto k = i->second.begin(); k != i->second.end();
                             k++) {
                                if (k->is_done())
                                        continue;
                                if (j != k && k->has_extra() && k->is_HDD()) {
                                        using prod = Product;
                                        string j_sz = get_hdd(*j, prod::HDD_sz);
                                        string k_sz = get_hdd(*k, prod::HDD_sz);
                                        string j_sp = get_hdd(*j, prod::HDD_sp);
                                        string k_sp = get_hdd(*k, prod::HDD_sp);
                                        string j_cp = get_hdd(*j, prod::HDD_cp);
                                        string k_cp = get_hdd(*k, prod::HDD_cp);
                                        if (((j_sz.empty() || k_sz.empty()) ||
                                             (j_sz == k_sz)) &&
                                            ((j_sp.empty() || k_sp.empty()) ||
                                             (j_sp == k_sp)) &&
                                            ((!j_cp.empty() && !k_cp.empty()) ||
                                             (j_cp == k_cp))) {
                                                j->substitude_PN(*k);
                                                if (j->is_done())
                                                        break;
                                        }
                                }
                        }
                }
        }
}

void RMA::substitude_PN()
{
        substitude_full_PN();
        substitude_HDD();
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
        if (m_info.find(rma_nm) == m_info.end()) {
                m_info[rma_nm].push_back(nf);
        } else {
                auto &vt = m_info.at(rma_nm);
                for (auto itr = vt.begin(); itr != vt.end(); ++itr) {
                        if (itr->m_pn == pn) {
                                proc_loc(*itr, tmp, qty);
                                return;
                        }
                }
                m_info[rma_nm].push_back(nf);
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
