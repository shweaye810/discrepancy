#include <iostream>
#include <string>
#include <vector>

#include "substitude.h"
#ifndef INFO_H
#define INFO_H

class Info {
public:
        Info(std::string part_n,
             std::string model,
             int qty,
             std::string loc);
        Info(const Info &o);
        friend std::ostream& operator<<(std::ostream &, const Info &);
private:
        std::string m_pn, m_mdl;
        int m_qty, xtr_qty, sb_tot_qty;
        std::string m_loc;
        std::vector<Substitude> m_sub;

};

#endif
