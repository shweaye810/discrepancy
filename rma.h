#include <map>

#include "info.h"
#include "tokenizer.h"

class RMA{
public:
        RMA();
        void add();
        void print(std::ostream &, const std::string &s) const;
        friend std::ostream& operator<<(std::ostream &, const RMA &);
        void RMA_PN_substitude();
        void RMA_qty_calc();
private:
        std::map<std::string, std::vector<Info> > m_info;
        void proc_loc(Info &, const std::string &, int);
};
