#include "tokenizer.h"

using namespace std;

stringstream Tokenizer::ss;

string Tokenizer::get_token()
{
        string tmp;
        getline(ss, tmp, '\t');
        return tmp;
}

void Tokenizer::set_string(string s)
{
        ss.str(s);
        ss.clear();
}
