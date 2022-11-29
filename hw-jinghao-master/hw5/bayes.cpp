#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <sstream>
#include <string>

using namespace std;

// calculate the probability Pr(C | X) using formula Pr(X | C) * Pr(C) / Pr(X | C) * Pr(C) + Pr(X | NotC) * Pr(NotC)
// where Pr(X1 & X2 & ... | C) = Pr(X1 | C) * Pr(X2 | C) * ...
// info is a set of attributes given for one line, trying to classify it using all attributes given
map<string, double> classifyingProbability(
        set<string>& info,
        map<string, map<string, int>>& attributeMap,
        map<string, int>& classifOccur,
        int numClassif) {
    // create a map prob with classification (C) as key and it's Pr(C | X) as value
    map<string, double> prob;
    // use iterator to iterate through every possible classification for one classifying unit
    map<string, int>::iterator it1;
    for (it1 = classifOccur.begin(); it1 != classifOccur.end(); ++it1) {
        // calculate Pr(C), Pr(NotC)
        // Pr(C) = occ(C) / total numbers of training units (numClassif)
        // Pr(NotC) = 1 - Pr(C)
        double probC = double(it1->second) / numClassif;
        double probNotC = 1.0 - probC;
        // calculate Pr(X|C), Pr(X|NotC)
        // set both to one
        double probCondC = 1.0;
        double probCondNotC = 1.0;
        // use iterator to loop through every attributes to caluculate Pr(X|C) and Pr(X|NotC) since
        // Pr(X1 & X2 & ... | C) = Pr(X1 | C) * Pr(X2 | C) * ... and
        // Pr(X1 & X2 & ... | NotC) = Pr(X1 | NotC) * Pr(X2 | NotC) * ...
        set<string>::iterator it2;
        for (it2 = info.begin(); it2 != info.end(); ++it2) {
            // count how many occurrence with Xi is not C
            // use iterator to loop through the map attributeMap[specific attribute]
            map<string, int>::iterator it3;
            double sumNotC = 0;
            for (it3 = attributeMap[*it2].begin(); it3 != attributeMap[*it2].end(); ++it3) {
                // attributeMap key as attribute and value as map of classifications(key) and occurence (value)
                // count how many occurence in total are not C
                if (it3->first != it1->first) {
                    sumNotC += it3->second;
                }
            }
            // check if certain C has such attributes in training data
            if (attributeMap[*it2].find(it1->first) != attributeMap[*it2].end()) {
                // if exists, using the formula Pr(Xi|C) = (1 + occ(Xi,C))/ (1 + occ(C))
                // Pr(Xi|C) = (1 + occ(Xi,NotC))/ (1 + occ(NotC)) = (1 + sumNotC)/ (1 + occ(NotC))
                // occ(Xi,C) can be found in attributeMap[Xi][C], occ(C) and occ(NotC) can be found in classifOccur
                probCondC *= (1 + attributeMap[*it2].find(it1->first)->second) / double(1 + it1->second);
                probCondNotC *= (1 + sumNotC) / double(1 + numClassif - it1->second);
            } else {
                // if not, using the formula Pr(Xi|C) = 1 / (1 + occ(C))
                // Pr(Xi|C) = (1 + occ(Xi,NotC))/ (1 + occ(NotC)) = (1 + sumNotC)/ (1 + occ(NotC))
                // where occ(C) and occ(NotC) can be found in classifOccur
                probCondC *= 1 / double(1 + it1->second);
                probCondNotC *= (1 + sumNotC) / double(1 + numClassif - it1->second);
            }
        }
        // insert the pair with C as key and probabilty of Pr(C|X) as value into map prob
        prob[it1->first] = (probCondC * probC) / (probCondC * probC + probCondNotC * probNotC);
    }
    // return prob
    return prob;
}

// get the classification with biggest probability for each classifying unit
string classifyingAnswer(map<string, double>& prob) {
    // use iterator to loop through the prob map to find the maximum probability and return the classification
    map<string, double>::iterator it;
    // create variable result to store the final classification name
    string result;
    // create variable max to keep track of max probability so far, set to 0
    double max = 0;
    for (it = prob.begin(); it != prob.end(); ++it) {
        // if the new probability >= max, then update result and max
        if (isgreaterequal(it->second, max)) {
            result = it->first;
            max = it->second;
        }
    }
    // return result
    return result;
}

int main(int argc, char* argv[]) {
    // check if correct number of documents are provided
    if (argc < 4) {
        // if missing file needed, print out the message as below
        cerr << "Please specify a training, classifying and output file" << endl;
        return 0;
    }

    // creat input file stream ifile1 to read training data
    ifstream ifile1(argv[1]);
    // create string variable line to temporarily store the line string in the input file
    string line;
    // create a stringstream ss to be used to convert line string into separable classifications and attributes
    stringstream ss;
    // create string variable classif to temporarily store the classification
    string classif;
    // create string variable attribute to temporarily store the classification of traning data
    string attribute;
    // create int variable numClassif to denote the number of items in the training data,
    // also the line numbers of the training file
    int numClassif;
    // get the first line in the training data file
    // get numClassif
    getline(ifile1, line);
    ss << line;
    ss >> numClassif;

    // create a map attributeMap with attributes as key, a map (key: the classifications and
    // value: corresponding occurrence of that attribute and the classifications) as value
    map<string, map<string, int>> attributeMap;
    // create a map classifOccur with classifications as key, number of occurrence as values
    map<string, int> classifOccur;

    // for loop to get data from training file to fill in the attributeMap and classifOccur
    for (int i = 0; i < numClassif; ++i) {
        // get the line for one training unit
        getline(ifile1, line);
        // create a stringstream ss2 to store the line and divide into classifications and attributes
        stringstream ss2(line);
        // get the classification for the training unit
        ss2 >> classif;

        // check if this classification is in the classifOccur
        if (classifOccur.find(classif) == classifOccur.end()) {
            // if not, add this classifOccur as key with value of 1
            classifOccur[classif] = 1;
        } else {
            // if exists, increment the occurrence for this classfication
            classifOccur[classif]++;
        }

        // create a set attributeSet to store all the attributes, to avoid repeat
        set<string> attributeSet;

        // get the attributes for this training unit into attributeSet
        // while we can subtract attributes from ss2
        while (ss2 >> attribute) {
            attributeSet.insert(attribute);
        }
        // use iterator to loop through non-repeatable attributes
        set<string>::iterator it;
        for (it = attributeSet.begin(); it != attributeSet.end(); ++it) {
            // for each attribute, check if it has been inside attributeMap
            if (attributeMap.find(*it) == attributeMap.end()) {
                // if not, create a map with key as corresponding classfication and value of 1
                // add this map as value and attribute as key into attribute Map
                map<string, int> tempMap;
                tempMap[classif] = 1;
                attributeMap[*it] = tempMap;
            } else {
                // if attribute exists
                // check if the correpsonding values in attributeMap has this classification
                if (attributeMap[*it].find(classif) == attributeMap[*it].end()) {
                    // if not, add this classif as key and 1 as value as a map being the value
                    // of this attribute in attributeMap
                    attributeMap[*it][classif] = 1;
                } else {
                    // if exists, increment the occurence
                    attributeMap[*it][classif]++;
                }
            }
        }
    }
    // close the input file stream for training input file
    ifile1.close();

    // creat input file stream ifile1 to read classifying data
    ifstream ifile2(argv[2]);
    // create a stringstream ss3 to be used to convert line string into separable attributes
    stringstream ss3;
    // creat output file stream ofile to write in the outputfile
    ofstream ofile(argv[3]);

    // create int variable numPredict to denote the number of items needed to predict in the classifying data,
    // and it is also the line number in the classifying file
    int numPredict;
    // get the first line in the classifying data file, numPredict
    getline(ifile2, line);
    ss3 << line;
    ss3 >> numPredict;

    // use for loop to predict each classifying unit for different possible classifications
    for (int i = 0; i < numPredict; ++i) {
        // create a set info to store the informations given (attributes)
        set<string> info;
        // get the line for one classifying unit
        getline(ifile2, line);
        // create a stringstream ss4 to store the line and divide into classifications and attributes
        stringstream ss4(line);
        // get the attributes for this classifying unit
        // while we can subtract attributes from ss4
        while (ss4 >> attribute) {
            // add the attribute to the set info
            info.insert(attribute);
        }

        // Call function classifyingProbability to get the map with classification as key and its probability as value
        map<string, double> resultMap = classifyingProbability(info, attributeMap, classifOccur, numClassif);
        // output the result with biggest probability to output file
        // check if it is last line, if it is, don't print a newline
        if (i == numPredict - 1) {
            // if it is last line, don't print a newline
            ofile << classifyingAnswer(resultMap);
        } else {
            // else if it's not last line, print a new line
            ofile << classifyingAnswer(resultMap) << endl;
        }
    }

    // close input file stream and output file stream
    ifile2.close();
    ofile.close();
}