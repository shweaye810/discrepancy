#include <map>

#include "info.h"
#include "tokenizer.h"

class RMA{
public:
        RMA();
        void add();
        friend std::ostream& operator<<(std::ostream &, const RMA &);
private:
        std::map<std::string, std::vector<Info> > m_info;
};
