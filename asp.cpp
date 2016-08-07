#include <sstream>

#include "asp.h"

using namespace std;

ASP::ASP()
{
}
/*
 * add() - fill data for ASP
 * @s: a row of input data
 *
 * sets string in Tokenizer and get token. if asp_nm is already in the map
 * append it, else add to the map.
 */
void ASP::add(string s)
{
        Tokenizer::set_string(s);
        string asp_nm = Tokenizer::get_token();
        if (m_row.find(asp_nm) == m_row.end()) {
                RMA rma;
                rma.add();
                m_row[asp_nm] = rma;
        } else {
                RMA &tmp_rma = m_row[asp_nm];
                tmp_rma.add();
        }
}

/*
 * print() - print all ASP and RMA
 *
 * for each row, print ASP and let RMA::print() do the rest.
 */
void ASP::print(ostream &out)
{
        for (auto itr = m_row.begin(); itr != m_row.end(); ++itr) {
                itr->second.print(out, itr->first);
        }
}

/*
 * calc_qty() - calculate the quantity: needed or extra
 *
 * for each ASP, call the helper function from RMA class to calculate the
 * quantity.
 */
void ASP::calc_qty()
{
        for (auto itr = m_row.begin(); itr != m_row.end(); ++itr) {
                itr->second.calc_qty();
        }
}

/*
 * substitute_PN() - substitute PN for all ASP
 *
 * for each ASP, call the helper function from RMA class to substitute PN.
 */
void ASP::substitute_PN()
{
        for (auto itr = m_row.begin(); itr != m_row.end(); ++itr) {
                itr->second.substitute_PN();
        }
}
