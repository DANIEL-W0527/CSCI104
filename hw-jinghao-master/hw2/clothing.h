#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// class Clothing publicly inherited from Product Class
class Clothing : public Product {
public:
    // Constructor
    Clothing(
            const std::string category,
            const std::string name,
            double price,
            int qty,
            std::string size,
            std::string brand);

    // Destructor
    ~Clothing();

    // pure virtual function in Product Class: keywords
    std::set<std::string> keywords() const;

    // pure virtual function in Product Class: keywords
    std::string displayString() const;

    // function to output information in database format
    void dump(std::ostream& os) const;

    // get function for Size
    std::string getSize() const;

    // get function for Brand
    std::string getBrand() const;

protected:
    std::string size_;
    std::string brand_;
};
#endif