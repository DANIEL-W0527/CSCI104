#include "clothing.h"

#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

// use initializer to define the constructor
Clothing::Clothing(
        const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
        : Product(category, name, price, qty) {
    size_ = size;
    brand_ = brand;
}

// Destructor
Clothing::~Clothing() {}

// parse name and brand into two sets of strings
// take union of two sets
std::set<std::string> Clothing::keywords() const {
    std::set<std::string> nameSet = parseStringToWords(name_);
    std::set<std::string> brandSet = parseStringToWords(brand_);
    std::set<std::string> clothingKeywords = setUnion(nameSet, brandSet);
    return clothingKeywords;
}

// display the string according to the format
std::string Clothing::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

// output info in database format
void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

// get function for size
std::string Clothing::getSize() const { return size_; }

// get function for brand
std::string Clothing::getBrand() const { return brand_; }