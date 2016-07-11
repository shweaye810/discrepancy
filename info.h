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
        void substitude_PN(Info &o);
        const std::string &model() const;
        bool has_extra();
private:
        std::string m_pn, m_mdl;
        int m_elm, m_rtv, xtr_qty, m_sub_tot;
        std::map<std::string, int> m_sub;
        bool is_HDD() const;
        bool is_MB() const;
        bool is_battery() const;
        bool is_adapter() const;

};

#endif
