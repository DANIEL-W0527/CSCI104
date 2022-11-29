#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "book.h"
#include "clothing.h"
#include "datastore.h"
#include "movie.h"
#include "product.h"
#include "user.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class MyDataStore : public DataStore {
public:
    ~MyDataStore();

    // Add a product to myDataStore
    void addProduct(Product* p);

    // Adds a user to myDataStore
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    // Reproduce the database file from the current Products and User values
    void dump(std::ostream& ofile);

    // adding product to user's cart
    void addingToCarts(std::vector<Product*> hits, std::string userName, int hit_result_index);

    // view certain user's cart
    void viewCart(std::string userName);

    // buy products for certain user
    void buyCart(std::string userName);

private:
    // map with keyword as key, and a set of product pointer as value
    std::map<std::string, std::set<Product*>> keywordMap;
    std::map<std::string, User*> userMap;
    std::vector<Product*> productsVec;
    std::vector<User*> usersVec;
    std::map<User*, std::vector<Product*>> userCart;
};
#endif