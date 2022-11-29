#include "util.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;
std::string convToLower(std::string src) {
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
    std::set<std::string> wordSet;
    // trim rawWords before continuing
    rawWords = trim(rawWords);
    // start keep track of the start point of the substr
    unsigned int start = 0;
    // loop through the character in the rawWords
    for (unsigned int i = 0; i < rawWords.length(); i++) {
        // if the character is punctuations, then check the substr before
        // this puctuation after the start point
        if (ispunct(rawWords.at(i)) || isspace(rawWords.at(i))) {
            // insert the lowercase of substr into the set if it's bigger than 2 characters
            if (i - start >= 2) {
                wordSet.insert(convToLower(rawWords.substr(start, i - start)));
            }
            // set new start point at next position after the punctuation
            start = i + 1;
        }
    }
    // if no punctuations until the end and the length is bigger than 2
    // then insert lowercase of it into the set
    if (rawWords.length() - start >= 2) {
        wordSet.insert(convToLower(rawWords.substr(start, rawWords.length() - start)));
    }
    return wordSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string& trim(std::string& s) { return ltrim(rtrim(s)); }
