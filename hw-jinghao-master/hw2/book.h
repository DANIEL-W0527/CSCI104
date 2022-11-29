#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// class Book publicly inherited from Product Class
class Book : public Product {
public:
    // Constructor
    Book(const std::string category,
         const std::string name,
         double price,
         int qty,
         std::string isbn,
         std::string author);

    // Destructor
    ~Book();

    // pure virtual function in Product Class: keywords
    std::set<std::string> keywords() const;

    // pure virtual function in Product Class: keywords
    std::string displayString() const;

    // function to output information in database format
    void dump(std::ostream& os) const;

    // get function for ISBN
    std::string getISBN() const;

    // get function for Author
    std::string getAuthor() const;

protected:
    std::string isbn_;
    std::string author_;
};
#endif