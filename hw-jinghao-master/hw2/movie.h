#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// class Movie publicly inherited from Product Class
class Movie : public Product {
public:
    // Constructor
    Movie(const std::string category,
          const std::string name,
          double price,
          int qty,
          std::string genre,
          std::string rating);

    // Destructor
    ~Movie();

    // pure virtual function in Product Class: keywords
    std::set<std::string> keywords() const;

    // pure virtual function in Product Class: keywords
    std::string displayString() const;

    // function to output information in database format
    void dump(std::ostream& os) const;

    // get function for Genre
    std::string getGenre() const;

    // get function for Rating
    std::string getRating() const;

protected:
    std::string genre_;
    std::string rating_;
};
#endif