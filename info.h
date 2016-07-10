#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef INFO_H
#define INFO_H


/*
 * @map<string, int> m_sub: string holds pn, int holds sz
 *
 */
class Info {
public:
        Info(std::string part_n, std::string model);
        Info(const Info &o);
        friend std::ostream& operator<<(std::ostream &, const Info &);
        friend class RMA;
        bool is_done();
        void calc_qty();
        int extra_qty() const;
private:
        std::string m_pn, m_mdl;
        int m_elm, m_rtv, xtr_qty, m_sub_tot;
        std::map<std::string, int> m_sub;
};

#endif
