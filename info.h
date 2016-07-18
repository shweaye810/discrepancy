#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "product.h"

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
        Product_type product() const;
private:
        std::string m_pn, m_mdl;
        int m_elm, m_rtv, xtr_qty, m_sub_tot;
        std::map<std::string, int> m_sub;
        Product_type prod_t;
        bool is_HDD() const;
        bool is_MB() const;
        bool is_BATT() const;
        bool is_adapter() const;
        bool is_LCD() const;
        bool is_DDR() const;
        bool is_SSD() const;
        void set_product_type();
};

#endif
