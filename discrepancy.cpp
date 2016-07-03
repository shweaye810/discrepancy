#include <fstream>
#include <iostream>
#include <sstream>

#include "asp.h"
#include "tokenizer.h"

using namespace std;

void print_error(const string &file_nm){
        cout << "Error opening " << file_nm << ".\n" << flush;
}
int main()
{
        ofstream fout;
        ifstream fin;
        string in_nm("test.txt"), out_nm("output.txt"), tmp, row;
        cout << "Trying to open test.txt.\n";
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
        int i = 0;
        do {
                stringstream ss;
                getline(fin, row);
                list.add(row);
                cout << list;

                /*
                  ss.str(tmp);
                  for (int i = 0; getline(ss, tmp, '\t'); ++i) {
                  fout << "i = " << i << ". " << tmp << " ";
                  }
                  fout << endl;
                */
                cout << i << endl;
                ++i;
        } while(fin.good());
        fin.close();
        fout.close();
        cout << "End of program.\n" << flush;
        return 0;
}
