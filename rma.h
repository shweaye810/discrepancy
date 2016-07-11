#include <map>

#include "info.h"
#include "tokenizer.h"

#ifndef RMA_H
#define RMA_H

class RMA{
public:
        RMA();
        void add();
        void print(std::ostream &, const std::string &s) const;
        friend std::ostream& operator<<(std::ostream &, const RMA &);
        void substitude_PN();
        void calc_qty();
private:
        std::map<std::string, std::vector<Info> > m_info;
        void proc_loc(Info &, const std::string &, int);
        void substitude_full_PN();
        void substitude_HDD();
};

#endif
