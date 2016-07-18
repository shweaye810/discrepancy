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
                                        if (j->is_done())
                                                break;
                                }
                        }
                }
        }
}

string get_substr(const Info &o, const regex &rg)
{
        smatch tmp;
        regex_search(o.model(), tmp, rg);
        return tmp[0];
}

bool is_same_HDD(const Info &l, const Info &r)
{
        string l_len(get_substr(l, regex_string::HDD_len));
        string r_len(get_substr(r, regex_string::HDD_len));
        string l_sp(get_substr(l, regex_string::HDD_speed));
        string r_sp(get_substr(r, regex_string::HDD_speed));
        string l_cap(get_substr(l, regex_string::HDD_cap));
        string r_cap(get_substr(r, regex_string::HDD_cap));
        return (((l_len.empty() || r_len.empty()) || l_len == r_len) &&
                ((l_sp.empty() || r_sp.empty()) || l_sp == r_sp) &&
                (!l_cap.empty() && !r_cap.empty() && l_cap == r_cap));
}

bool is_same_SSD(const Info &l, const Info &r)
{
        string l_len(get_substr(l, regex_string::HDD_len));
        string r_len(get_substr(r, regex_string::HDD_len));
        string l_cap(get_substr(l, regex_string::HDD_cap));
        string r_cap(get_substr(r, regex_string::HDD_cap));
        return (((l_len.empty() || r_len.empty()) || l_len == r_len) &&
                (!l_cap.empty() && !r_cap.empty() && l_cap == r_cap));
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
                                        bool eq = is_same_HDD(*j, *k);
                                        if (eq) {
                                                j->substitude_PN(*k);
                                                if (j->is_done())
                                                        break;
                                        }
                                }
                        }
                }
        }
}

string get_product_model(string s)
{
        stringstream sstrm(s);
        sstrm >> s;
        return s;
}
bool is_same_MB(const Info &l, const Info &r)
{
        string l_mdl(get_product_model(l.model()));
        string r_mdl(get_product_model(r.model()));
        string l_cpu(get_substr(l, regex_string::CPU_model));
        string r_cpu(get_substr(r, regex_string::CPU_model));

        return ((!(l_mdl.empty() || r_mdl.empty()) && l_mdl == r_mdl) &&
                ((l_cpu.empty() || r_cpu.empty()) || l_cpu == r_cpu));
}

bool is_same_adapter(const Info &l, const Info &r)
{
        string l_wat(get_substr(l, regex_string::adapter_watt));
        string r_wat(get_substr(r, regex_string::adapter_watt));
        string l_volt(get_substr(l, regex_string::adapter_volt));
        string r_volt(get_substr(r, regex_string::adapter_volt));

        return (((l_wat.empty() || r_wat.empty()) || l_wat == r_wat) &&
                ((l_volt.empty() || r_volt.empty()) || l_volt == r_volt));
}

bool is_same_BATT(const Info &l, const Info &r)
{
        string l_mdl(get_product_model(l.model()));
        string r_mdl(get_product_model(r.model()));

        return (!(l_mdl.empty() || r_mdl.empty()) && l_mdl == r_mdl);
}

bool is_same_LCD(const Info &l, const Info &r)
{
        string l_size(get_substr(l, regex_string::LCD_size));
        string r_size(get_substr(r, regex_string::LCD_size));

        return (!(l_size.empty() || r_size.empty()) && l_size == r_size);
}

bool is_same_DDR(const Info &l, const Info &r)
{
        string l_size(get_substr(l, regex_string::DDR_size));
        string r_size(get_substr(r, regex_string::DDR_size));
        string l_speed(get_substr(l, regex_string::DDR_speed));
        string r_speed(get_substr(r, regex_string::DDR_speed));

        return ((!(l_size.empty() || r_size.empty()) && l_size == r_size) &&
                (!(l_speed.empty() || r_speed.empty()) && l_speed == r_speed));
}

bool is_same_model(const Info &l, const Info &r)
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
                cout << "check is_same_model().\nModel: " << l.model() << '\n';
                break;
        }
        return false;
}

void RMA::substitude_all()
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
                                        bool eq = is_same_model(*j, *k);
                                        if (eq) {
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
        //        substitude_HDD();
        substitude_all();
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
