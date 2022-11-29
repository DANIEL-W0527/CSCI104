#include "Hashtable.h"

#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

// Consructor
Hashtable::Hashtable(bool debug, unsigned int probing) {
    // assign value of debug to debug_, probing to probing_,
    // initialize size_ with 11, loaded_ with 0, sizeIndex with 0
    debug_ = debug;
    probing_ = probing;
    size_ = 11;
    loaded_ = 0;
    sizeIndex_ = 0;

    // check if it has debug mode
    // if without debug mode, charge r value to five random numbers between 0 and size_ - 1 (inclusive)
    if (!debug_) {
        for (int i = 0; i < 5; ++i) {
            r[i] = rand() % size_;
        }
    }

    // create an array of string-int pairs of length size_
    data = new std::pair<string, int>[size_];
}

// destructor
Hashtable::~Hashtable() {
    // deallocate memory
    delete[] data;
}

// add string k to Hashtable
void Hashtable::add(const std::string& k) {
    // check if loading factor is at least 0.5
    // if it is, call resize
    if (isgreaterequal(((double)loaded_) / size_, 0.5)) {
        resize();
    }

    // if the loading factor is less than 0.5, there is a place for string k
    // Check the probing index sequence, if we found an index has that string, increment the value
    // if we found an empty index and all previous indices does not have string k,
    // it means string k is not in the sequence

    // get the hash value from the primary hash function
    int hashVal = hash(k);

    // check the probing to decide the behavior of colliding key
    // if linear probing is used
    if (probing_ == 0) {
        // since loading factor < 1, size_ is prime, there will be a place eventually for any string
        // while the string at index is not empty, keep updating hashVal by 1
        while (data[hashVal].first != "") {
            // if at that index, it has same string as k, increment the value
            if (data[hashVal].first == k) {
                data[hashVal].second++;
                // done!
                return;
            }
            // else some other string, updating hashVal
            hashVal = (hashVal + 1) % size_;
        }
        // found an empty index and all previous indices do not have string k,
        // it means string k is not in the Hashtable
        // assign the string at that index with occurrence of 1
        data[hashVal].first = k;
        data[hashVal].second = 1;
        // update loaded_ by 1
        loaded_++;
        // done!
        return;
    }
    // if quadratic probing is used
    else if (probing_ == 1) {
        // since loading factor < 1, size_ is prime, there will be a place eventually for any string
        // create int j to track number of times changing hashVal,
        // create int temp to copy hashVal to be used later without changing hashVal
        int j = 1;
        int temp = hashVal;
        // while loop, keep looping if there is string taking up the index
        while (data[temp].first != "") {
            // if at that index, it has same string as k, increment the value
            if (data[temp].first == k) {
                data[temp].second++;
                // done!
                return;
            }
            // else some other string, updating temp
            temp = (hashVal + j * j) % size_;
            // increment j
            j++;
        }
        // found an empty index and all previous indices do not have string k,
        // it means string k is not in the Hashtable
        // assign the string at that index with occurrence of 1
        data[temp].first = k;
        data[temp].second = 1;
        // update loaded_ by 1
        loaded_++;
        // done
        return;
    }
    // if double hashing is uesed
    else {
        // since loading factor < 1, size_ is prime, there will be a place eventually for any string
        // get the hash value from the second hash function
        int secondHashVal = secondHash(k);
        // create int j to track number of times changing hashVal,
        // create int temp to copy hashVal to be used later without changing hashVal
        int j = 1;
        int temp = hashVal;
        // while loop, keep looping if there is string taking up the index
        while (data[temp].first != "") {
            // if at that index, it has same string as k, increment the value
            if (data[temp].first == k) {
                data[temp].second++;
                // done!
                return;
            }
            // else some other string, updating temp
            temp = (hashVal + j * secondHashVal) % size_;
            // increment j
            j++;
        }
        // found an empty index and all previous indices do not have string k,
        // it means string k is not in the Hashtable
        // assign the string at that index with occurrence of 1
        data[temp].first = k;
        data[temp].second = 1;
        // update loaded_ by 1
        loaded_++;
        // done
        return;
    }
}

// count occurrence of string k in hashtable
int Hashtable::count(const string& k) {
    // get the hash value from the primary hash function
    int hashVal = hash(k);

    // check the probing method
    // if linear probing is used
    if (probing_ == 0) {
        // since loading factor < 1, size_ is prime, if k is in the Hashtable,
        // it will find the index following the sequence before hitting the empty index
        // there are empty spaces, so if k is not in string we would not search more than size_ times
        // staring at hashVal and check if at that index has string k
        // if we encounter an empty index, it means string k is not in the Hashtable

        // while the string at index is not empty, keep updating hashVal by 1
        while (data[hashVal].first != "") {
            // if at that index, it has same string as k, return the value
            if (data[hashVal].first == k) {
                return data[hashVal].second;
            }
            // else updating hashVal
            hashVal = (hashVal + 1) % size_;
        }
        // found an empty index, it means string k is not in the Hashtable
        return 0;
    }
    // if quadratic probing is used
    else if (probing_ == 1) {
        // since loading factor < 1, size_ is prime, if k is in the Hashtable,
        // it will find the index following the sequence before hitting the empty index
        // staring at hashVal and check if at that index has string k
        // if we encounter an empty index, it means string k is not in the Hashtable
        // create int j to track number of times changing hashVal,
        // create int temp to copy hashVal to be used later without changing hashVal
        int j = 1;
        int temp = hashVal;

        // while the string at index is not empty, keep updating hashVal
        while (data[temp].first != "") {
            // if at that index, it has same string as k, return the value
            if (data[temp].first == k) {
                return data[temp].second;
            }
            // else updating temp
            temp = (hashVal + j * j) % size_;
            // increment j
            j++;
        }
        // found an empty index, it means string k is not in the Hashtable
        return 0;
    }
    // if double hashing is uesed
    else {
        // since loading factor < 1, size_ is prime, if k is in the Hashtable,
        // it will find the index following the sequence before hitting the empty index
        // staring at hashVal and check if at that index has string k
        // if we encounter an empty index, it means string k is not in the Hashtable

        // since loading factor < 1, size_ is prime, there will be a place eventually for any string
        // get the hash value from the second hash function
        int secondHashVal = secondHash(k);

        // create int j to track number of times changing hashVal,
        // create int temp to copy hashVal to be used later without changing hashVal
        int j = 1;
        int temp = hashVal;

        // while the string at index is not empty, keep updating hashVal
        while (data[temp].first != "") {
            // if at that index, it has same string as k, return the value
            if (data[temp].first == k) {
                return data[temp].second;
            }
            // else updating temp
            temp = (hashVal + j * secondHashVal) % size_;
            // increment j
            j++;
        }
        // found an empty index, it means string k is not in the Hashtable
        return 0;
    }
}

// print the strings and their occurrence in hashtable in the output file
void Hashtable::reportAll(ostream& out) const {
    // for loop to loop through the Hashtable to print string and its frequency
    for (int i = 0; i < size_; ++i) {
        // check if index is empty, only ouput non-empty indices
        if (data[i].first != "") {
            out << data[i].first << " " << data[i].second << endl;
        }
    }
}

// change the size of data, rehash all the strings in Hashtbale into the new Hashtable
void Hashtable::resize() {
    // copy pointer of old data array to dataCopy
    pair<string, int>* dataCopy = data;
    // update the size_ to next size in the sequence above
    size_ = sizeArr[sizeIndex_ + 1];
    // update sizeIndex_
    sizeIndex_++;
    // update new r values if without debug node
    if (!debug_) {
        for (int i = 0; i < 5; ++i) {
            r[i] = rand() % size_;
        }
    }

    // rehash strings in the previous Hashtable
    // create an array of string-int pairs of length size_
    data = new std::pair<string, int>[size_];
    // rehash all the non-empty strings into data
    // after resizing, it guaranteed to find an index for every string in the previous Hashtable
    for (int j = 0; j < sizeArr[sizeIndex_ - 1]; ++j) {
        // check if string at that index is empty
        // if string at that index is not empty
        if (dataCopy[j].first != "") {
            // hash the string and put it into Hashtable
            resizeAdd(dataCopy[j].first, dataCopy[j].second);
        }
    }
    // deallocate dataCopy
    delete[] dataCopy;
}

// when resizing, add all strings already in Hashtable into new Hashtable
void Hashtable::resizeAdd(const std::string& k, int freq) {
    /* since this function is called after resizing, transfering all input strings into larger Hashtable
     * loading factor is guaranteed to be less than 0.5, do not need to consider about resizing again
     */

    /* all indices has differnt strings since we already increment the value before if it's the same string
     * and store it into Hashtable, no need to check duplicate keys
     */

    // get the hash value from the primary hash function
    int hashVal = hash(k);

    // check the probing to decide the behavior of colliding key
    // if linear probing is used
    if (probing_ == 0) {
        // since loading factor < 1, size_ is prime, there will be a place eventually for any string
        // while loop to find an empty place since all strings are different in old Hashtable
        while (data[hashVal].first != "") {
            // updating hashVal
            hashVal = (hashVal + 1) % size_;
        }
        // found an empty index
        // assign the string at that index with same occurence before
        data[hashVal].first = k;
        data[hashVal].second = freq;
        // done!
        return;
    }
    // if quadratic probing is used
    else if (probing_ == 1) {
        // since loading factor < 1, size_ is prime, there will be a place eventually for any string
        // create int j to track number of times changing hashVal,
        // create int temp to copy hashVal to be used later without changing hashVal
        int j = 1;
        int temp = hashVal;
        // while loop to find an empty place since all strings are different in old Hashtable
        while (data[temp].first != "") {
            // update temp
            temp = (hashVal + j * j) % size_;
            // increment j
            j++;
        }
        // found an empty index
        // assign the string at that index with with same occurence before
        data[temp].first = k;
        data[temp].second = freq;
        // done
        return;
    }
    // if double hashing is uesed
    else {
        // since loading factor < 1, size_ is prime, there will be a place eventually for any string
        // get the hash value from the second hash function
        int secondHashVal = secondHash(k);
        // create int j to track number of times changing hashVal,
        // create int temp to copy hashVal to be used later without changing hashVal
        int j = 1;
        int temp = hashVal;
        // while loop to find an empty place since all strings are different in old Hashtable
        while (data[temp].first != "") {
            // update temp
            temp = (hashVal + j * secondHashVal) % size_;
            // increment j
            j++;
        }
        // found an empty index
        // assign the string at that index with occurrence of 1
        data[temp].first = k;
        data[temp].second = freq;
        // done
        return;
    }
}

// get hash value for string k using the primary hash function
int Hashtable::hash(const string& k) const {
    // convert string into value
    // create an int array w to store w values
    // initialize with 0
    int w[5] = {0, 0, 0, 0, 0};
    // call function calculateW to calculate w values
    calculateW(k, w);

    // creata long long sum to store the sum of product ri * wi, i is from 0 to 4 (inclusive)
    long long sum = 0;
    // for loop to get the sum of product ri * wi, i is from 0 to 4 (inclusive)
    for (int k = 0; k < 5; ++k) {
        sum += (long long)((long long)w[k] * (long long)r[k]);
    }
    // return the hash value
    return sum % size_;
}

// get hash value for string k using the second hash function
int Hashtable::secondHash(const string& k) const {
    // convert string into value
    // create an int array w to store w values
    // initialize with 0
    int w[5] = {0, 0, 0, 0, 0};
    // call function calculateW to calculate w values
    calculateW(k, w);
    // return hash value
    return (long long)((long long)p[sizeIndex_] - (((long long)w[0] + (long long)w[1] + (long long)w[2] + (long long)w[3] + (long long)w[4]) % (long long)p[sizeIndex_]));
}

// caluculate the w values for string k
void Hashtable::calculateW(const string& k, int* w) const {
    // check how many complete strings of length 6 and store it in numLengthSix
    int numLengthSix = k.size() / 6;
    // check how long is the left string(not enough 6 string), and store it in leftLength
    int leftLength = k.size() % 6;

    // for loop to get the correpsonding w value for complete 6 strings
    for (int j = 0; j < numLengthSix; ++j) {
        w[4 - j] = calculateLengthSixValue(k.substr(k.size() - (j + 1) * 6, 6));
    }

    // check if there is string less than 6 left
    // if there is string less than 6 left
    if (leftLength != 0) {
        // calculate the w value for this string
        w[4 - numLengthSix] = calculateLessSixValue(k.substr(0, leftLength), leftLength);
    }
}

// calculate the w value for string of length 6
int Hashtable::calculateLengthSixValue(const string& k) const {
    return pow(26, 5) * ((int)(k.at(0)) - 97) + pow(26, 4) * ((int)(k.at(1)) - 97) + pow(26, 3) * ((int)(k.at(2)) - 97)
           + pow(26, 2) * ((int)(k.at(3)) - 97) + 26 * ((int)(k.at(4)) - 97) + ((int)(k.at(5)) - 97);
}

// calculate the w value for string of length less than 6
int Hashtable::calculateLessSixValue(const string& k, int length) const {
    int sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += pow(26, i) * ((int)(k.at(length - 1 - i)) - 97);
    }
    return sum;
}