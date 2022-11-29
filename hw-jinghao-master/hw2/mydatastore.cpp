#include "mydatastore.h"

#include "util.h"
#include <cmath>
#include <iostream>
#include <sstream>

MyDataStore::~MyDataStore() {
    std::vector<Product*>::iterator it1;
    std::vector<User*>::iterator it2;
    for (it1 = productsVec.begin(); it1 != productsVec.end(); ++it1) {
        delete *it1;
    }
    for (it2 = usersVec.begin(); it2 != usersVec.end(); ++it2) {
        delete *it2;
    }
}

// Add a product to myDataStore
// add product to productsVec
// modify the keywordMap when adding a product
void MyDataStore::addProduct(Product* p) {
    productsVec.push_back(p);
    // get set of the keyword for this product
    std::set<std::string> productKeyword = p->keywords();
    // create a Product* set with only this product pointer
    std::set<Product*> tempSet;
    tempSet.insert(p);
    // iterate through this product's keyword set
    std::set<std::string>::iterator it;
    for (it = productKeyword.begin(); it != productKeyword.end(); ++it) {
        // if the keyword is already in the keywordMap, the add p to that keyword's set
        if (keywordMap.find(*it) != keywordMap.end()) {
            keywordMap[*it].insert(p);
        }
        // if keyword is not in keywordMap, add pair (keyword, set of p) into the keywordMap
        else {
            keywordMap[*it] = tempSet;
        }
    }
}

// Add a user to myDataStore
// add user to usersVec, map between user's name and user's pointer
void MyDataStore::addUser(User* u) {
    // add user to usersVac
    usersVec.push_back(u);
    // map between user's name and user's pointer
    userMap[u->getName()] = u;
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> result;
    // if there is no terms input
    if (terms.size() == 0) {
        // return all product* if type is 0
        if (type == 0) {
            return productsVec;
        }
    }
    // if there is only one term, no difference between differnt type
    else if (terms.size() == 1) {
        // check if the term in a valid keyword in keywordMap
        if (keywordMap.find(terms[0]) != keywordMap.end()) {
            // create a set to store the product*, and convert to a vector
            std::set<Product*> resultSet = keywordMap[terms[0]];
            result.assign(resultSet.begin(), resultSet.end());
        }
    }
    // if theree is more than one term
    else {
        std::set<Product*> resultSet;
        // check all the terms if it is in keywordMap
        // store valid keyword in vector validKeyword
        std::vector<std::string> validKeyword;
        std::vector<std::string>::iterator it1;
        // iterate through vector terms
        for (it1 = terms.begin(); it1 != terms.end(); ++it1) {
            // if the term is found in keywordMap, add to keyword
            if (keywordMap.find(*it1) != keywordMap.end()) {
                validKeyword.push_back(*it1);
            }
        }

        // search according to the type
        std::vector<std::string>::iterator it2;
        // if seach with AND
        if (type == 0) {
            // if validKeyword has same number of elements as terms
            // return intersection set of all terms
            // otherwise, there is no product macthing
            if (validKeyword.size() == terms.size()) {
                // iterate through validKeyword
                for (it2 = validKeyword.begin(); it2 != validKeyword.end(); ++it2) {
                    // set resultset = the first keyword's product set at first
                    if (it2 == validKeyword.begin()) {
                        resultSet = keywordMap[*it2];
                    }
                    // for other keywords, set result = intersection of set result
                    // and keywords's product set
                    else {
                        resultSet = setIntersection(resultSet, keywordMap[*it2]);
                    }
                }
                // convert set to vector
                result.assign(resultSet.begin(), resultSet.end());
            }
        }
        // if seach with OR
        else if (type == 1) {
            // iterate through validKeyword and find the union of prduct* set
            std::vector<std::string>::iterator it2;
            for (it2 = validKeyword.begin(); it2 != validKeyword.end(); ++it2) {
                // set resultset = the first keyword's product set at first
                if (it2 == validKeyword.begin()) {
                    resultSet = keywordMap[*it2];
                }
                // for other keywords, set result = union of set result
                // and keywords's product set
                else {
                    resultSet = setUnion(resultSet, keywordMap[*it2]);
                }
            }
            // convert set to vector
            result.assign(resultSet.begin(), resultSet.end());
        }
    }
    return result;
}

// Reproduce the database file from the current Products and User values
void MyDataStore::dump(std::ostream& ofile) {
    std::vector<Product*>::iterator it1;
    std::vector<User*>::iterator it2;
    // print products section
    ofile << "<products>" << std::endl;
    // iterate through all Product* and output database format
    for (it1 = productsVec.begin(); it1 != productsVec.end(); ++it1) {
        (*it1)->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    // print users section
    ofile << "<users>" << std::endl;
    // iterate through all User* and output database format
    for (it2 = usersVec.begin(); it2 != usersVec.end(); ++it2) {
        (*it2)->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

// adding product to user's cart
void MyDataStore::addingToCarts(std::vector<Product*> hits, std::string userName, int hit_result_index) {
    // check if userName is valid, then find the User* with userName as key in userMap
    User* usr;
    if (userMap.find(userName) != userMap.end()) {
        usr = userMap[userName];
    } else {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    // ind the user's cart vector with User* as key in userCart
    // add the Product* to that user's cart vector
    userCart[usr].push_back(hits[hit_result_index - 1]);
}

// view certain user's cart
void MyDataStore::viewCart(std::string userName) {
    // check if userName is valid, then find the User* with userName as key in userMap
    User* usr;
    if (userMap.find(userName) != userMap.end()) {
        usr = userMap[userName];
    } else {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    // if empty, display "Empty cart"
    if (userCart[usr].empty()) {
        std::cout << "Empty cart" << std::endl;
    } else {
        // find the user's cart vector with User* as key in userCart
        // loop through the cart vector print out user's cart
        for (unsigned int i = 0; i < userCart[usr].size(); i++) {
            std::cout << "Item " << i + 1 << std::endl;
            std::cout << userCart[usr][i]->displayString() << std::endl;
            std::cout << std::endl;
        }
    }
}

// buy products for certain user
void MyDataStore::buyCart(std::string userName) {
    // check if userName is valid, then find the User* with userName as key in userMap
    User* usr;
    if (userMap.find(userName) != userMap.end()) {
        usr = userMap[userName];
    } else {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // loop through user's cart
    unsigned int i = 0;
    while (i < userCart[usr].size()) {
        // if product is in stock and user' balance is enough
        if (userCart[usr][i]->getQty() >= 1 && std::isgreaterequal(usr->getBalance(), userCart[usr][i]->getPrice())) {
            // decrement the product quantity by 1
            userCart[usr][i]->subtractQty(1);
            // deduct the price of product from user's balance
            usr->deductAmount(userCart[usr][i]->getPrice());
            // remove the product
            userCart[usr].erase(userCart[usr].begin() + i);
            // adjust the value of i
            // if product is removed, then i stays the same
        }
        // if not check the next product
        else {
            i++;
        }
    }
}