#include <string>
#include <vector>

#ifndef PRODUCT_H
#define PRODUCT_H

class Product {
public:
        static std::vector<std::string> HDD_sz, HDD_sp, HDD_cp;
        static void init();
private:
        Product();
};

#endif
