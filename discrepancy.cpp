#include <fstream>
#include <iostream>

#include "asp.h"

using namespace std;

int main()
{
        ofstream fout;
        ifstream fin;
        string file_nm("test.txt"), tmp;
        cout << "Trying to open test.txt.\n";
        fin.open(file_nm.c_str());
        /*
        cout << "Please enter the file name: " << flush ;
        cin >> file_nm;
        fin.open(file_nm.str());
        */
        if(!fin.is_open()) {
                cout << "Error opening " << file_nm << ".\n" << flush;
                return -1;
        }
        do {
                getline(fin, tmp);
        } while(fin.good());
        return 0;
}
