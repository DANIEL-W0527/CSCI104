#include "Hashtable.h"
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

// trim the string word to only contain letters, convert it to lowercase string
string trimWord(string word) {
    // create a string trimmed to store the final result only have lowercase letters
    string trimmed = "";
    // iterate through each character in word
    for (string::iterator it = word.begin(); it != word.end(); ++it) {
        // check if the character is a letter
        if (isalpha(*it)) {
            // if it is a letter
            // check if it is a lowercase letter
            if ((int)(*it) <= 90) {
                // if not, add lowercase letter to trimmed
                trimmed += (char)((int)(*it) + 32);
            } else {
                // if it is, directly add this letter to trimmed
                trimmed += *it;
            }
        }
    }
    // return trimmed
    return trimmed;
}

int main(int argc, char* argv[]) {
    // check if correct number of command line arguments are provided
    if (argc < 6) {
        // if missing command line arguments needed, print out the message as below
        cerr << "Please specify all arguments needed" << endl;
        return 0;
    }
    // creat input file stream ifile to read input file
    ifstream ifile(argv[1]);
    // create output file stream ofile to write in output file
    ofstream ofile(argv[2]);
    // create int x to store value of x
    int x = atoi(argv[3]);
    // create int d to store value of x
    int d = atoi(argv[4]);
    // create int x to store value of x
    int r = atoi(argv[5]);
    // create string line to temporarily store the line in input file
    string line;
    // create string word to temporarily store the word
    string word;
    // create string trimmedWord to temporarily store the trimmed lowercase word
    string trimmedWord;
    // create a vector of string words to store all the trimmed words in input file
    vector<string> words;

    // while we can subtract the line from input file
    while (getline(ifile, line)) {
        // create stringstream to subtract words from line
        stringstream ss(line);
        // for each line, subtract word spliting by whitespace
        while (ss >> word) {
            // call function trimWord to trim word
            trimmedWord = trimWord(word);
            // check if the trimmedWord is greater than 28 characters
            if (trimmedWord.size() > 0 && trimmedWord.size() <= 28) {
                // if the trimmedWord is less than 28 characters and is not empty,add to vector words
                // or discard the word if longer than 28 characters or it's empty
                words.push_back(trimmedWord);
            }
        }
    }
    // close input file stream
    ifile.close();

    // start timing
    clock_t start;
    double duration;
    start = clock();

    // repeat for r times
    for (int i = 0; i < r; ++i) {
        // check x value to see use Hashtable or map
        if (x != 3) {
            // use Hashtable
            Hashtable ht = Hashtable(!!d, x);
            // add every element in words into ht
            for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
                ht.add(*it);
            }
        } else {
            // use map
            // create a map with string as key and its number of occurence as value
            map<string, int> mp;
            // add every element in words into ht
            for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
                // check if the word is already in the map
                // if the word is already in the map, increment the value by 1
                if (mp.find(*it) != mp.end()) {
                    mp[*it]++;
                }
                // if the word is not in the map, add to map with value of 1
                else {
                    mp[*it] = 1;
                }
            }
        }
    }
    // record the total time for r repeats
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;

    // count the occurrence of words
    // create a map with word as key and its occurrence as values
    map<string, int> freqCount;
    for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
        // check if the word is already in the map
        // if the word is already in the map, increment the value by 1
        if (freqCount.find(*it) != freqCount.end()) {
            freqCount[*it]++;
        }
        // if the word is not in the map, add to map with value of 1
        else {
            freqCount[*it] = 1;
        }
    }

    // output the method used
    ofile << "Method: ";
    if (x == 0) {
        if (d == 0) {
            ofile << "Hashtable using linear probing without debug mode" << endl;
        } else {
            ofile << "Hashtable using linear probing with debug mode" << endl;
        }
    } else if (x == 1) {
        if (d == 0) {
            ofile << "Hashtable using quadratic probing without debug mode" << endl;
        } else {
            ofile << "Hashtable using quadratic probing with debug mode" << endl;
        }
    } else if (x == 2) {
        if (d == 0) {
            ofile << "Hashtable using double-hashing without debug mode" << endl;
        } else {
            ofile << "Hashtable using double-hashing with debug mode" << endl;
        }
    } else {
        ofile << "STL Map" << endl;
    }

    // output size of words
    ofile << "There are " << words.size() << " words in total" << endl;

    // out put total repeat times:
    ofile << "Repeat for " << r << " times" << endl;

    // ouput time result into output file
    ofile << "Time spent on one repeat on average: " << duration / r << endl;
    ofile << "Time spent on one operation on average: " << (duration / r) / words.size() << endl;

    // iterate through freqcount to output all words and its recurrence
    ofile << "\nAll Words and its occurrence:" << endl;
    for (map<string, int>::iterator it1 = freqCount.begin(); it1 != freqCount.end(); ++it1) {
        ofile << it1->first << ": " << it1->second << endl;
    }

    // close output file stream
    ofile.close();
}
