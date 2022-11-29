#include "movie.h"

#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

// use initializer to define the constructor
Movie::Movie(
        const std::string category,
        const std::string name,
        double price,
        int qty,
        std::string genre,
        std::string rating)
        : Product(category, name, price, qty) {
    genre_ = genre;
    rating_ = rating;
}

// Destructor
Movie::~Movie() {}

// parse name a set of strings
// take union of the set and the genre
std::set<std::string> Movie::keywords() const {
    std::set<std::string> movieKeywords = parseStringToWords(name_);
    movieKeywords.insert(convToLower(genre_));
    return movieKeywords;
}

// display the string according to the format
std::string Movie::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

// output info in database format
void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

// get function for Genre
std::string Movie::getGenre() const { return genre_; }

// get function for Rating
std::string Movie::getRating() const { return rating_; }