/* Write your test code for the ULListStr in this file */

#include "ulliststr.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    ULListStr t1;
    string val[10] = {"1", "12", "28", "57", "58", "67", "23", "62", "79", "13"};
    string val2[5] = {"11", "2", "43", "42", "25"};
    string fs;
    string bs;

    // Test 1 for push_back function
    cout << "1. Test for push_back function" << endl << endl;
    cout << "(1) An empty list" << endl << endl;
    t1.push_back("1");
    cout << t1.get(0) << endl;
    cout << "Size: " << t1.size() << endl << endl;

    cout << "(2) A non-empty list with 1 or more values but <= 10" << endl << endl;
    for (int i = 1; i < 10; i++) {
        t1.push_back(val[i]);
        for (int j = 0; j <= i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "Size: " << t1.size() << endl;
        cout << endl;
    }
    cout << endl;

    // 10 the boundary point for arraysize
    cout << "(3) A non-empty list with elements > 10" << endl << endl;
    for (int i = 0; i < 5; i++) {
        t1.push_back(val2[i]);
        for (int j = 0; j <= 10 + i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "Size: " << t1.size() << endl;
        cout << endl;
    }
    cout << endl;

    // Test 2 for pop_back and back function
    cout << "2. Test for pop_back and back function" << endl << endl;
    cout << "(1) A non-empty list with elements > 10" << endl << endl;
    for (int i = 14; i >= 10; i--) {
        bs = t1.back();
        cout << "Last String: " << bs << endl;
        cout << "Original Size: " << t1.size() << endl;
        t1.pop_back();
        for (int j = 0; j < i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "New size: " << t1.size() << endl;
        cout << endl;
    }

    cout << "(2) A non-empty list with elements >=2 and <= 10" << endl << endl;
    for (int i = 9; i >= 1; i--) {
        bs = t1.back();
        cout << "Last String: " << bs << endl;
        cout << "Original Size: " << t1.size() << endl;
        t1.pop_back();
        for (int j = 0; j < i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "New size: " << t1.size() << endl;
        cout << endl;
    }

    cout << "(3) A non-empty list with 1 element" << endl << endl;
    bs = t1.back();
    cout << "Last String: " << bs << endl;
    cout << "Original Size: " << t1.size() << endl;
    t1.pop_back();
    cout << "New size: " << t1.size() << endl << endl;

    cout << "(4) An empty list" << endl << endl;
    // back function won't be applied to an empty list
    cout << "Original Size: " << t1.size() << endl;
    t1.pop_back();
    cout << "New size: " << t1.size() << endl << endl;

    // Test 3 for push_front function
    cout << "3. Test for push_front function" << endl << endl;
    cout << "(1) An empty list" << endl << endl;
    t1.push_front("1");
    cout << t1.get(0) << endl;
    cout << "Size: " << t1.size() << endl << endl;

    cout << "(2) A non-empty list with 1 or more values but <= 10" << endl << endl;
    for (int i = 1; i < 10; i++) {
        t1.push_front(val[i]);
        for (int j = 0; j <= i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "Size: " << t1.size() << endl;
        cout << endl;
    }
    cout << endl;

    // 10 the boundary point for arraysize
    cout << "(3) A non-empty list with elements > 10" << endl << endl;
    for (int i = 0; i < 5; i++) {
        t1.push_front(val2[i]);
        for (int j = 0; j <= 10 + i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "Size: " << t1.size() << endl;
        cout << endl;
    }
    cout << endl;

    // Test 4 for pop_front and front function
    cout << "4. Test for pop_front and front function" << endl << endl;
    cout << "(1) A non-empty list with elements > 10" << endl << endl;
    for (int i = 14; i >= 10; i--) {
        fs = t1.front();
        cout << "First String: " << fs << endl;
        cout << "Original Size: " << t1.size() << endl;
        t1.pop_front();
        for (int j = 0; j < i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "New size: " << t1.size() << endl;
        cout << endl;
    }

    cout << "(2) A non-empty list with elements >=2 and <= 10" << endl << endl;
    for (int i = 9; i >= 1; i--) {
        fs = t1.front();
        cout << "First String: " << fs << endl;
        cout << "Original Size: " << t1.size() << endl;
        t1.pop_front();
        for (int j = 0; j < i; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "New size: " << t1.size() << endl;
        cout << endl;
    }

    cout << "(3) A non-empty list with 1 element" << endl << endl;
    fs = t1.front();
    cout << "First String: " << fs << endl;
    cout << "Original Size: " << t1.size() << endl;
    t1.pop_front();
    cout << "New size: " << t1.size() << endl << endl;

    cout << "(4) An empty list" << endl << endl;
    // front function won't be applied to an empty list
    cout << "Original Size: " << t1.size() << endl;
    t1.pop_front();
    cout << "New size: " << t1.size() << endl << endl;

    // Test 5 for mixed use of push_back and push_front functions
    cout << "5. Test for mixed use of push_back and push_front function" << endl << endl;
    cout << "(1) An empty list" << endl << endl;
    t1.push_front(val[0]);
    t1.push_back(val[1]);
    cout << t1.get(0) << " " << t1.get(1) << endl;
    cout << "Size: " << t1.size() << endl << endl;

    cout << "(2) A non-empty list with 2 or more values but <= 10" << endl << endl;
    for (int i = 2; i < 10; i = i + 2) {
        t1.push_front(val[i]);
        t1.push_back(val[i + 1]);
        for (int j = 0; j <= i + 1; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "Size: " << t1.size() << endl;
        cout << endl;
    }
    cout << endl;

    // 10 the boundary point for arraysize
    cout << "(3) A non-empty list with elements > 10" << endl << endl;
    for (int i = 0; i < 4; i = i + 2) {
        t1.push_front(val2[i]);
        t1.push_back(val2[i + 1]);
        for (int j = 0; j <= 10 + i + 1; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "Size: " << t1.size() << endl;
        cout << endl;
    }
    cout << endl;

    // Test 6 for mixed use of pop_back, pop_front(), back and front functions
    cout << "6. Test for mixed use of pop_back, pop_front, back, and front fuctions" << endl << endl;
    cout << "(1) A non-empty list with elements > 10" << endl << endl;
    for (int i = 13; i >= 10; i = i - 2) {
        fs = t1.front();
        bs = t1.back();
        cout << "First String: " << fs << endl;
        cout << "Last String: " << bs << endl;
        cout << "Original Size: " << t1.size() << endl;
        t1.pop_front();
        t1.pop_back();
        for (int j = 0; j < i - 1; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "New size: " << t1.size() << endl;
        cout << endl;
    }

    cout << "(2) A non-empty list with elements >=2 and <= 10" << endl << endl;
    for (int i = 9; i >= 2; i = i - 2) {
        fs = t1.front();
        bs = t1.back();
        cout << "First String: " << fs << endl;
        cout << "Last String: " << bs << endl;
        cout << "Original Size: " << t1.size() << endl;
        t1.pop_front();
        t1.pop_back();
        for (int j = 0; j < i - 1; j++) {
            cout << t1.get(j) << " ";
        }
        cout << endl;
        cout << "New size: " << t1.size() << endl;
        cout << endl;
    }

    cout << "(3) A non-empty list with 2 element" << endl << endl;
    fs = t1.front();
    bs = t1.back();
    cout << "First String: " << fs << endl;
    cout << "Last String: " << bs << endl;
    cout << "Original Size: " << t1.size() << endl;
    t1.pop_front();
    t1.pop_back();
    cout << "New size: " << t1.size() << endl << endl;

    cout << "(4) An empty list" << endl << endl;
    // back and front function won't be applied to an empty list
    cout << "Original Size: " << t1.size() << endl;
    t1.pop_front();
    t1.pop_back();
    cout << "New size: " << t1.size() << endl << endl;

    return 0;
}
