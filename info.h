#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef INFO_H
#define INFO_H

class Info {
public:
        Info(std::string part_n, std::string model);
        Info(const Info &o);
        friend std::ostream& operator<<(std::ostream &, const Info &);
        friend class RMA;
private:
        std::string m_pn, m_mdl;
        int m_elm, m_rtv, xtr_qty;
        std::map<std::string, int> m_sub;
};

#endif
