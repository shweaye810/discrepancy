#include <cstdlib>
#include <exception>
#include <sstream>
#include <vector>
#include <regex>

#include "rma.h"
#include "regex_string.cpp"
using namespace std;

RMA::RMA()
{
}

/*
 * lower(string) - make all string to lower case
 *
 * for each char in s, change it to lower case.
 */
string lower(string s)
{
        for (auto itr = s.begin(); itr != s.end(); ++itr) {
                *itr = tolower(*itr);
        }
        return s;
}
/*
 * proc_loc(Info &, string &, int) - add qty to it's location
 * @nf: info
 *
 * if tmp is rtv, then add qty to rtv, elm other wise.
 */
inline void RMA::proc_loc(Info &nf, const string &tmp, int qty)
{
        if (tmp == "rtv") {
                nf.m_rtv += qty;
        } else if (tmp == "elm") {
                nf.m_elm += qty;
        }
}

/*
 * substitude_full_PN() - substitute PN if description matches exactly.
 *
 * for each info, if it's done skip, else find info that has extra qty.
 * if both description matches, then substitute PN.
 */
void RMA::substitute_full_PN()
{
        for (auto i = m_info.begin(); i != m_info.end(); i++) {
                for (auto j = i->second.begin(); j != i->second.end(); j++) {
                        if (j->is_done() || j->xtr_qty >= 0)
                                continue;
                        for (auto k = i->second.begin(); k != i->second.end();
                             k++) {
                                if (k->is_done() || j == k || k->xtr_qty < 0)
                                        continue;
                                if (j->m_dscr.find(k->m_dscr) != string::npos ||
                                    k->m_dscr.find(j->m_dscr) != string::npos) {
                                        j->substitute_PN(*k);
                                        if (j->is_done())
                                                break;
                                }
                        }
                }
        }
}

/*
 * get_substr() - get the substr from description
 * @o: other
 * @RE: regular expression
 *
 * return string from description that matches RE.
 */
string get_substr(const Info &o, const regex &RE)
{
        smatch tmp;
        regex_search(o.description(), tmp, RE);
        return tmp[0];
}

/*
 * is_same_HDD() - return true if the two HDD are the same
 *
 * if both len, sp, and cap are equal, then return true, false otherwise.
 */
bool is_same_HDD(const Info &l, const Info &r)
{
        string l_len(get_substr(l, regex_string::HDD_len));
        string r_len(get_substr(r, regex_string::HDD_len));
        string l_sp(get_substr(l, regex_string::HDD_speed));
        string r_sp(get_substr(r, regex_string::HDD_speed));
        string l_cap(get_substr(l, regex_string::storage_cap));
        string r_cap(get_substr(r, regex_string::storage_cap));
        return (((l_len.empty() || r_len.empty()) || l_len == r_len) &&
                ((l_sp.empty() || r_sp.empty()) || l_sp == r_sp) &&
                (!l_cap.empty() && !r_cap.empty() && l_cap == r_cap));
}

/*
 * is_same_SSD - return true if two SSD are the same
 *
 * refer to is_same_HDD for full comment.
 */
bool is_same_SSD(const Info &l, const Info &r)
{
        string l_len(get_substr(l, regex_string::HDD_len));
        string r_len(get_substr(r, regex_string::HDD_len));
        string l_cap(get_substr(l, regex_string::storage_cap));
        string r_cap(get_substr(r, regex_string::storage_cap));
        return (((l_len.empty() || r_len.empty()) || l_len == r_len) &&
                (!l_cap.empty() && !r_cap.empty() && l_cap == r_cap));
}

/*
 * get_product_model() - return model of this string(description)
 */
string get_product_model(string s)
{
        stringstream sstrm(s);
        sstrm >> s;
        return s;
}

/*
 * is_same_MB - return true if two MB are the same
 *
 * refer to is_same_HDD for full comment.
 */
bool is_same_MB(const Info &l, const Info &r)
{
        string l_mdl(get_product_model(l.description()));
        string r_mdl(get_product_model(r.description()));
        string l_cpu(get_substr(l, regex_string::CPU_model));
        string r_cpu(get_substr(r, regex_string::CPU_model));
        string l_gb(get_substr(l, regex_string::storage_cap));
        string r_gb(get_substr(r, regex_string::storage_cap));

        return ((!(l_mdl.empty() || r_mdl.empty()) && l_mdl == r_mdl) &&
                ((l_cpu.empty() || r_cpu.empty()) || l_cpu == r_cpu) &&
                ((l_gb.empty() || r_gb.empty()) || l_gb == r_gb));
}
/*
 * is_same_adapter - return true if two adapter are the same
 *
 * refer to is_same_HDD for full comment.
 */
bool is_same_adapter(const Info &l, const Info &r)
{
        string l_wat(get_substr(l, regex_string::adapter_watt));
        string r_wat(get_substr(r, regex_string::adapter_watt));
        string l_volt(get_substr(l, regex_string::adapter_volt));
        string r_volt(get_substr(r, regex_string::adapter_volt));

        return (((l_wat.empty() || r_wat.empty()) || l_wat == r_wat) &&
                ((l_volt.empty() || r_volt.empty()) || l_volt == r_volt));
}

/*
 * is_same_BATT - return true if two batter are the same
 *
 * refer to is_same_HDD for full comment.
 */
bool is_same_BATT(const Info &l, const Info &r)
{
        string l_mdl(get_product_model(l.description()));
        string r_mdl(get_product_model(r.description()));

        return (!(l_mdl.empty() || r_mdl.empty()) && l_mdl == r_mdl);
}

/*
 * is_same_LCD - return true if two LCD are the same
 *
 * refer to is_same_HDD for full comment.
 */
bool is_same_LCD(const Info &l, const Info &r)
{
        string l_size(get_substr(l, regex_string::LCD_size));
        string r_size(get_substr(r, regex_string::LCD_size));

        return (!(l_size.empty() || r_size.empty()) && l_size == r_size);
}

/*
 * is_same_DDR - return true if two DDR are the same
 *
 * refer to is_same_HDD for full comment.
 */
bool is_same_DDR(const Info &l, const Info &r)
{
        string l_size(get_substr(l, regex_string::DDR_size));
        string r_size(get_substr(r, regex_string::DDR_size));
        string l_speed(get_substr(l, regex_string::DDR_speed));
        string r_speed(get_substr(r, regex_string::DDR_speed));

        return ((!(l_size.empty() || r_size.empty()) && l_size == r_size) &&
                (!(l_speed.empty() || r_speed.empty()) && l_speed == r_speed));
}
/*
 * is_same_description() - return true if both description are the same.
 */
bool is_same_description(const Info &l, const Info &r)
{
        switch(l.product()) {
        case Product_type::adapter:
                return is_same_adapter(l, r);
        case Product_type::BATT:
                return is_same_BATT(l, r);
        case Product_type::DDR:
                return is_same_DDR(l, r);
        case Product_type::HDD:
                return is_same_HDD(l, r);
        case Product_type::LCD:
                return is_same_LCD(l, r);
        case Product_type::MB:
                return is_same_MB(l, r);
        case Product_type::SSD:
                return is_same_SSD(l, r);
        default:
                cout << "check is_same_description().\nModel: " << l.description() << '\n';
                break;
        }
        return false;
}

/*
 * substitude_all() - substitute PN of all infos
 *
 * refer to substitute_full_PN() for full comment
 */
void RMA::substitute_all()
{
        for (auto i = m_info.begin(); i != m_info.end(); i++) {
                for (auto j = i->second.begin(); j != i->second.end(); j++) {
                        if (j->is_done() || j->has_extra())
                                continue;
                        for (auto k = i->second.begin(); k != i->second.end();
                             k++) {
                                if (k->is_done())
                                        continue;
                                if (j != k && k->has_extra() &&
                                    (k->product() == j->product())) {
                                        bool eq = is_same_description(*j, *k);
                                        if (eq) {
                                                j->substitute_PN(*k);
                                                if (j->is_done())
                                                        break;
                                        }
                                }
                        }
                }
        }
}

/*
 * substitute_PN() - name says all.
 */
void RMA::substitute_PN()
{
        substitute_full_PN();
        substitute_all();
}

/*
 * add() - add info to RMA
 *
 * Get all info for Info members, process location. If RMA doesn't exists, map
 * RMA and Info, else find info. If found, add qty to the info, else,
 * add new info to Info container.
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
        nf.set_product_type();
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

/*
 * print() - print the each RMA and Info
 *
 * for each rma, print infos.
 */
void RMA::print(ostream &cout, const std::string &s) const
{
        for (auto i = this->m_info.begin(); i != this->m_info.end(); ++i) {
                auto &v = i->second;
                for (auto ii = v.begin(); ii != v.end(); ++ii) {
                        cout << s << '\t' << i->first << '\t' << *ii << endl;
                }
        }
}

/*
 * calc_qty() - calculate quantity
 *
 * for each rma, calculate each info's qty.
 */
void RMA::calc_qty()
{
        for (auto i = m_info.begin(); i != m_info.end(); ++i) {
                auto &v = i->second;
                for (auto ii = v.begin(); ii != v.end(); ++ii) {
                        ii->calc_qty();
                }
        }
}
