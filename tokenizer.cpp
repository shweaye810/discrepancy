#include "tokenizer.h"

using namespace std;

stringstream Tokenizer::ss;

/*
 * get_token() - return token from a string
 */
string Tokenizer::get_token()
{
        string tmp;
        getline(ss, tmp, '\t');
        return tmp;
}

/*
 * set_string() - set the string to be tokenize
 */
void Tokenizer::set_string(string s)
{
        ss.str(s);
        ss.clear();
}
