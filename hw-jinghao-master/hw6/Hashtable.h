#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

class Hashtable {
public:
    // Consructor
    Hashtable(bool debug = false, unsigned int probing = 0);
    // destructor
    ~Hashtable();
    // add string k to Hashtable
    void add(const std::string& k);
    // count occurrence of string k in hashtable
    int count(const std::string& k);
    // print the strings and their occurrence in hashtable in the output file
    void reportAll(std::ostream& out) const;

private:
    // change the size of data, rehash all the strings in Hashtbale into the new Hashtable
    void resize();
    // when resizing, add all strings already in Hashtable into new Hashtable
    void resizeAdd(const std::string& k, int freq);
    // get hash value for string k using the primary hash function
    int hash(const std::string& k) const;
    // get hash value for string k using second hash function
    int secondHash(const std::string& k) const;
    // caluculate the w values for string k
    void calculateW(const std::string& k, int* w) const;
    // calculate the w value for string of length 6
    int calculateLengthSixValue(const std::string& k) const;
    // calculate the w value for string of length less than 6
    int calculateLessSixValue(const std::string& k, int length) const;
    // array of string, integer pairs to store data of Hashtable
    std::pair<std::string, int>* data;
    // store the debug mode, true for with debug mode, false for without debug mode
    bool debug_;
    // store the size of Hashtable
    int size_;
    // store the probing method used, 0 for linear probing, 1 for quadratic probing, 2 for double-hashing
    unsigned int probing_;
    // store the number of indices taken by strings in Hashtable
    int loaded_;
    // store the index of the Hashtable size in given Hashtable Size sequence,
    // also the prime number index used for specific Hashtable size in sequences of prime numbers
    int sizeIndex_;
    // array of int, store the sequences of Hashtable size
    int sizeArr[28]
            = {11,       23,       47,       97,        197,       397,       797,       1597,      3203,    6421,
               12853,    25717,    51437,    102877,    205759,    411527,    823117,    1646237,   3292489, 6584983,
               13169977, 26339969, 52679969, 105359969, 210719881, 421439783, 842879579, 1685759167};
    // array of int, store the sequences of prime number used in second hash function
    int p[28] = {7,        19,       43,       89,        193,       389,       787,       1583,      3191,    6397,
                 12841,    25703,    51431,    102871,    205721,    411503,    823051,    1646221,   3292463, 6584957,
                 13169963, 26339921, 52679927, 105359939, 210719881, 421439749, 842879563, 1685759113};
    // store the r values for debug mode, would change this if debug mode is not used
    int r[5] = {983132572, 62337998, 552714139, 984953261, 261934300};
};

#endif