#include <cctype>

#include "info.h"

using namespace std;

/*
 * Info() - constructor of Info that takes two agruments
 * @part_n: part number
 * @descrip: description
 *
 * Initialize PN and description and the rest to 0.
 */
Info::Info(string part_n, string descrip) :
        m_pn(part_n), m_dscr(descrip), m_elm(0), m_rtv(0), xtr_qty(0),
        m_sub_tot(0), prod_t(Product_type::NA)
{

}

/*
 * Info(Const Info &) - Copy o to this
 * o: other
 *
 * Copy all the members of o to this.
 */
Info::Info(const Info &o) :
        m_pn(o.m_pn), m_dscr(o.m_dscr), m_elm(o.m_elm), m_rtv(o.m_rtv),
        xtr_qty(o.xtr_qty), m_sub_tot(o.m_sub_tot), m_sub(o.m_sub),
        prod_t(o.prod_t)
{
}

/*
 * operator<<() overload
 */
ostream& operator<<(ostream &cout, const Info &info)
{
        cout << info.m_pn << '\t' << info.m_dscr << '\t' << info.m_elm << '\t'
             << info.m_rtv << '\t'<< info.xtr_qty << '\t'
             << info.m_sub_tot << '\t';

        for (auto itr = info.m_sub.begin(); itr != info.m_sub.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\t';
        }

        return cout;
}

/*
 * is_done() - return true if this row is done
 */
bool Info::is_done()
{
        return xtr_qty == 0;
}
/*
 * calc_qty() - calculate the extra qty of this row
 *
 * calculate extra qty. extra qty = elm - rtv + sub_tot
 */
void Info::calc_qty()
{
        xtr_qty = m_elm - m_rtv + m_sub_tot;
}

int Info::extra_qty() const
{
        return xtr_qty;
}

/*
 * is_HDD() - return true if description is HDD
 *
 * if description contains SATA, but SSD, then return true, false otherwies.
 */
bool Info::is_HDD() const
{
        return m_dscr.find("SATA") != string::npos &&
                m_dscr.find("SSD") == string::npos;
}

/*
 * is_MB() - return true if description is motherboard
 *
 * if description contains MB or MAIN, then return true.
 */
bool Info::is_MB() const
{
        return m_dscr.find("MB") != string::npos ||
                m_dscr.find("MAIN") != string::npos;
}

/*
 * is_BATT() - return true if description is battery
 *
 * if description contains BATT or BAT, then return true.
 */
bool Info::is_BATT() const
{
        return m_dscr.find("BATT") != string::npos ||
                m_dscr.find(" BAT") != string::npos;
}

bool Info::is_adapter() const
{
        return m_dscr.find("ADAPTER") != string::npos;
}

bool Info::is_LCD() const
{
        return m_dscr.find("LCD") != string::npos;
}

bool Info::is_DDR() const
{
        return m_dscr.find("DDR") != string::npos;
}

bool Info::is_SSD() const
{
        return m_dscr.find("SSD") != string::npos;
}

/*
 * get_qty(Info &, Info &) - get qty to substitute.
 * @l, r: left and right respectively
 *
 * if absolute of left is less than right, return absolute of less, right
 * otherwise.
 */
int get_qty(const Info &l, const Info &r)
{
        return abs(l.extra_qty()) < r.extra_qty() ?
                                    abs(l.extra_qty()) : r.extra_qty();
}

bool Info::has_extra()
{
        return xtr_qty > 0;
}

/*
 * substitutde_PN(Info &) - substitute the PN and qty with this and o
 * @o: other
 *
 * get the quantity to substitute. add other PN and qty to substitute container;
 * add qty to m_sub_tot. subtract qty form o. calculate final qty of this and o
 * by calling calc_qty().
 */
void Info::substitute_PN(Info &o)
{
        int qty = get_qty(*this, o);
        this->m_sub[o.m_pn] = qty;
        this->m_sub_tot += qty;
        o.m_sub_tot -= qty;
        this->calc_qty();
        o.calc_qty();
}

const string &Info::description() const
{
        return m_dscr;
}

/*
 * set_product_type() - set the product type of this
 *
 * if adapter, set it to adapter, etc.
 */
void Info::set_product_type()
{
        if (is_adapter()) {
                prod_t = Product_type::adapter;
        } else if (is_BATT()) {
                prod_t = Product_type::BATT;
        } else if (is_DDR()) {
                prod_t = Product_type::DDR;
        } else if (is_HDD()) {
                prod_t = Product_type::HDD;
        } else if (is_LCD()) {
                prod_t = Product_type::LCD;
        } else if (is_MB()) {
                prod_t = Product_type::MB;
        } else if (is_SSD()) {
                prod_t = Product_type::SSD;
        }
}
/*
 * product() - return product type of this
 */
Product_type Info::product() const
{
        return prod_t;
}
