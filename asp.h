#include "rma.h"

#ifndef ASP_H
#define ASP_H

/*
 * class ASP - an object to map ASP and RMA
 * @ m_row: string -> ASP
 *
 */
class ASP {
public:

        ASP();
        void add(std::string s);
        void print(std::ostream &);
        void substitute_PN();
        void calc_qty();
private:
        std::map<std::string, RMA> m_row;
};

#endif
