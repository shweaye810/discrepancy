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

void RMA::add()
{
        string rma_nm = Tokenizer::get_token();
        string pn = Tokenizer::get_token();
        string mdl = Tokenizer::get_token();
        int qty = stoi(Tokenizer::get_token());
        string loc = Tokenizer::get_token();
        string tmp(lower(loc));
        if (!m_info.empty() && m_info.find(rma_nm) != m_info.end()) {
                auto nf = m_info.at(rma_nm);
                for (auto itr = nf.begin(); itr != nf.end(); ++itr) {
                        if (itr->m_pn == pn) {
                                if (tmp == "rtv") {
                                        itr->m_rtv += qty;
                                } else if (tmp == "elm") {
                                        itr->m_elm += qty;
                                }
                        }
                }
        } else {
                Info nf(pn, mdl);
                if (tmp == "rtv") {
                        nf.m_rtv = qty;
                } else if (tmp == "elm") {
                        nf.m_elm = qty;
                }
                m_info[rma_nm].push_back(nf);
        }
}

ostream& operator<<(ostream &cout, const RMA &rma)
{
        for (auto itr = rma.m_info.begin(); itr != rma.m_info.end(); ++itr) {
                for (auto iitr = itr->second.begin();
                     iitr != itr->second.end();
                     ++iitr) {
                        cout << itr->first << '\t' << *iitr;
                }
        }
        return cout;

}
