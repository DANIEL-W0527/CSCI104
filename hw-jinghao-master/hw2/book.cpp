#include "book.h"

#include "util.h"
#include <iomanip>
#include <sstream>

using namespace std;

// use initializer to define the constructor
Book::Book(
        const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author)
        : Product(category, name, price, qty) {
    isbn_ = isbn;
    author_ = author;
}

// Destructor
Book::~Book() {}

// parse name and author into two sets of strings
// take union of two sets and the ISBN
std::set<std::string> Book::keywords() const {
    std::set<std::string> nameSet = parseStringToWords(name_);
    std::set<std::string> authorSet = parseStringToWords(author_);
    std::set<std::string> bookKeywords = setUnion(nameSet, authorSet);
    bookKeywords.insert(convToLower(isbn_));
    return bookKeywords;
}

// display the string according to the format
std::string Book::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

// output info in database format
void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

// get function for ISBN
std::string Book::getISBN() const { return isbn_; }

// get function for Author
std::string Book::getAuthor() const { return author_; }