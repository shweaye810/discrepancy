#include "rma.h"

using namespace std;

RMA::RMA()
{
}

void RMA::add()
{
        string rma_nm = Tokenizer::get_token();
        string pn = Tokenizer::get_token();
        string mdl = Tokenizer::get_token();
        int qty = stoi(Tokenizer::get_token());
        string loc = Tokenizer::get_token();
        Info nf(pn, mdl, qty, loc);
        m_info[rma_nm].push_back(nf);
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
