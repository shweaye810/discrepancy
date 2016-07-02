#include <string>
#include <vector>

#include "rma.h"

#ifndef ASP_H
#define ASP_H

class ASP {
public:

        ASP();
        void add(std::string s);
private:
        std::vector<RMA> nm;
};

#endif
