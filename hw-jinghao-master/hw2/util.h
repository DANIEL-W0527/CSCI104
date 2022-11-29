#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <set>
#include <string>

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template<typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2) {
    // create a new set to store the resulting set
    std::set<T> resultSet;
    typename std::set<T>::iterator it;
    // loop through s1, if the element also found in s2
    // then add that element to result set
    for (it = s1.begin(); it != s1.end(); ++it) {
        if (s2.find(*it) != s2.end()) {
            resultSet.insert(*it);
        }
    }
    return resultSet;
}
template<typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2) {
    // create a new set to store the resulting set
    std::set<T> resultSet;
    typename std::set<T>::iterator it;
    // copy all the elements in s1 into resultSet
    for (it = s1.begin(); it != s1.end(); ++it) {
        resultSet.insert(*it);
    }

    // loop through s2, add to resultSet
    // since insert will ignore the duplicate elements
    for (it = s2.begin(); it != s2.end(); ++it) {
        resultSet.insert(*it);
    }
    return resultSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string& ltrim(std::string& s);

// Removes any trailing whitespace
std::string& rtrim(std::string& s);

// Removes leading and trailing whitespace
std::string& trim(std::string& s);
#endif
