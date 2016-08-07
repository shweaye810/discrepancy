#include <map>

#include "info.h"
#include "tokenizer.h"

#ifndef RMA_H
#define RMA_H

/*
 * @m_info: string -> RMA
 */
class RMA{
public:
        RMA();
        void add();
        void print(std::ostream &, const std::string &s) const;
        void substitute_PN();
        void calc_qty();
private:
        std::map<std::string, std::vector<Info> > m_info;

        void proc_loc(Info &, const std::string &, int);
        void substitute_full_PN();
        void substitute_all();
};

#endif
