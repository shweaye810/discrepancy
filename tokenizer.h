#include <sstream>
#include <string>

#ifndef TOKENIZER_H
#define TOKENIZER_H

class Tokenizer {
public:
        static std::string get_token();
        static void set_string(std::string s);
private:
        static std::stringstream ss;
};

#endif
