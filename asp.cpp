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
        RMA rma;
        rma.add();
        m_row[asp_nm].push_back(rma);
}

ostream& operator<<(ostream &cout, const ASP &asp)
{
        for (auto itr = asp.m_row.begin(); itr != asp.m_row.end(); ++itr) {
                for (auto iitr = itr->second.begin();
                     iitr != itr->second.end();
                     ++iitr) {
                        cout << itr->first << '\t' << *iitr << endl;
                }
        }
        return cout;
}
