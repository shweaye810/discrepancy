#include "rma.h"

#ifndef ASP_H
#define ASP_H

class ASP {
public:

        ASP();
        void add(std::string s);
        friend std::ostream& operator<<(std::ostream &, const ASP &);
        void substitude_PN();
        void calc_qty();
private:
        std::map<std::string, RMA> m_row;
};

#endif
