#include <fstream>
#include <iostream>
#include <sstream>

#include "asp.h"
#include "tokenizer.h"

using namespace std;

void print_error(const string &file_nm)
{
        cout << "Error opening " << file_nm << ".\n" << flush;
}
int main()
{
        ofstream fout;
        ifstream fin;

        string in_nm("test.txt"), out_nm("output.txt"), tmp, row;
        cout << "Trying to open " << in_nm << ".\n";
        fin.open(in_nm.c_str());
        /*        cout << "Please enter the file name: " << flush ;
                  cin >> in_nm;
                  fin.open(in_nm.str());
        */
        if (!fin.is_open()) {
                print_error(in_nm);
                return -1;
        }

        fout.open(out_nm.c_str());
        if (!fout.is_open()) {
                print_error(out_nm);
                return -1;
        }
        ASP list;

        while (getline(fin, row)) {
                if (row.empty())
                        continue;
                stringstream ss;
                list.add(row);
                /*
                  ss.str(tmp);
                  for (int i = 0; getline(ss, tmp, '\t'); ++i) {
                  fout << "i = " << i << ". " << tmp << " ";
                  }
                  fout << endl;
                */
        }
        list.calc_qty();
        list.substitude_PN();
        fout << "ASP\tCOD\tASUS_PN\tPart_Name\tELM\tRTV\txtra_qty\t"
                "SUB_TOT_QTY\tSUB_PN\tSUB_QTY\n"
                ;
        fout << list;

        fin.close();
        fout.close();
        cout << "Data has been written into " << out_nm << ".\n";
        cout << "End of program.\n" << flush;
        return 0;
}
