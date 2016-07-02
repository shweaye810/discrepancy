#include <string>
#include <vector>

#include "substitude.h"
#ifndef INFO_H
#define INFO_H

class Info {
public:
        Info(std::string part_n, std::string model, int elm_qty, int rtv_qty);
private:
        std::string pn, mdl;
        int elm, rtv, xtr_qty, sb_tot_qty;
        std::vector<Substitude> sub;
};

#endif
