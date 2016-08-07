#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "product.h"

#ifndef INFO_H
#define INFO_H

/*
 * @m_pn: part number
 * @m_dscr: description
 * @map<string, int> m_sub: string -> pn, int -> sz
 * @prod_t: product type of this row
 */
class Info {
public:
        Info(std::string part_n, std::string dscr);
        Info(const Info &o);
        friend std::ostream& operator<<(std::ostream &, const Info &);
        friend class RMA;
        bool is_done();
        void calc_qty();
        int extra_qty() const;
        void substitute_PN(Info &o);
        const std::string &description() const;
        bool has_extra();
        Product_type product() const;
private:
        std::string m_pn, m_dscr;
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
