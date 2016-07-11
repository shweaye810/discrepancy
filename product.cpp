#include "product.h"

using namespace std;

vector<string> Product::HDD_sz;
vector<string> Product::HDD_sp;
vector<string> Product::HDD_cp;

void Product::init() {
        HDD_sz.push_back("2.5'");
        HDD_sz.push_back("3.5'");

        HDD_sp.push_back("5200R");
        HDD_sp.push_back("5400R");
        HDD_sp.push_back("5700R");
        HDD_sp.push_back("5900R");
        HDD_sp.push_back("7200R");
        HDD_sp.push_back("10000R");
        HDD_sp.push_back("10500R");
        HDD_sp.push_back("15000R");

        for (int i = 1; i <= 256; i++) {
                HDD_cp.push_back(i + "G");
        }

        HDD_cp.push_back("10TB");
        HDD_cp.push_back("8TB");
        HDD_cp.push_back("6TB");
        HDD_cp.push_back("5TB");
        HDD_cp.push_back("4TB");
        HDD_cp.push_back("3.8TB");
        HDD_cp.push_back("3.2TB");
        HDD_cp.push_back("3TB");
        HDD_cp.push_back("2.5TB");
        HDD_cp.push_back("2TB");
        HDD_cp.push_back("1.8TB");
        HDD_cp.push_back("1.6TB");
        HDD_cp.push_back("1.5TB");
        HDD_cp.push_back("1.2TB");
        HDD_cp.push_back("1TB");
        HDD_cp.push_back("960G");
        HDD_cp.push_back("900G");
        HDD_cp.push_back("800G");
        HDD_cp.push_back("750G");
        HDD_cp.push_back("640G");
        HDD_cp.push_back("600G");
        HDD_cp.push_back("512G");
        HDD_cp.push_back("500G");
        HDD_cp.push_back("480G");
        HDD_cp.push_back("460G");
        HDD_cp.push_back("450G");
        HDD_cp.push_back("400G");
        HDD_cp.push_back("360G");
        HDD_cp.push_back("320G");
        HDD_cp.push_back("300G");
}
