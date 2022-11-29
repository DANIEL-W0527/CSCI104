#include "avlbst.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct Rectangle {
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef AVLTree<int, Rectangle> InputMapType;
typedef AVLTree<int, std::pair<int, int>> OutputMapType;

// Allowed global variables: the dimensions of the grid
int n;  // X-dim size
int m;  // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    os << p.first << "," << p.second;
    return os;
}

void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output) {
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it) {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool>>& grid) {
    for (int x = x1; x < x1 + r.length; x++) {
        for (int y = y1; y < y1 + r.height; y++)
            grid[x][y] = !grid[x][y];
    }
}

// check if rectangle r starting at x1, y1 is out of the surface
// check if rectangle r starting at x1, y1 is overlapping with existing rectangles
bool isValidPlace(int x1, int y1, int length, int height, const Rectangle& r, vector<vector<bool>>& grid) {
    // check if rectangle r's starting point is out of the surface
    if (x1 < 0 || x1 >= length || y1 < 0 || y1 >= height) {
        return false;
    }
    // if rectangle r's starting point is in the surface
    // check if the entire rectangle r is in the surface
    if (x1 + r.length > length || x1 + r.length < 1 || y1 + r.height > height || y1 + r.height < 1) {
        return false;
    }

    // rectangle r starting at x1, y1 is inside the surface
    // check if rectangle is overlapping with existing rectangles
    for (int i = x1; i < x1 + r.length; ++i) {
        for (int j = y1; j < y1 + r.height; ++j) {
            if (grid[i][j] == true) {
                // if one of them is overlapping with existing rectangle
                // then it is not valid place
                return false;
            }
        }
    }
    // else it is a valid place
    return true;
}

// orient the rectangle
// swap the height and the length of the rectangle
void orient(Rectangle& r) {
    // swap the height and the length of the rectangle
    int temp = r.height;
    r.height = r.length;
    r.length = temp;
}

// TODO: Write your backtracking search function here
bool hasValidSolutions(
        InputMapType::iterator it,
        InputMapType& input,
        int length,
        int height,
        vector<vector<bool>>& grid,
        OutputMapType& output) {
    // if iterator reached to the end without returning true before
    // it means there is no solution
    if (it == input.end()) {
        return true;
    }

    // check if total area is bigger than the surface
    if (it == input.begin()) {
        int sumArea = 0;
        // use iterator to find sum of the input rectangles
        for (InputMapType::iterator it1 = input.begin(); it1 != input.end(); ++it1) {
            sumArea += (it1->second).length * (it1->second).height;
        }
        // if the total area of input rectangles is bigger than the surface
        // the solution does not exist
        if (sumArea > length * height) {
            return false;
        }
    }

    // if the iteator did not reached the end
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < height; ++j) {
            // check if the place is taken by others
            if (!grid[i][j]) {
                // check if the place is valid
                if (isValidPlace(i, j, length, height, it->second, grid)) {
                    // change the grid with correpsonding place
                    flip(i, j, it->second, grid);
                    // create a copy of it, so increment the copy will now change it
                    InputMapType::iterator itCopy = it;
                    // recursive call hasValidSolutions
                    // check if the rest of input triangles could be placed
                    if (hasValidSolutions(++itCopy, input, length, height, grid, output)) {
                        output.insert(make_pair(it->first, make_pair(i, j)));
                        // Found Solution!
                        return true;
                    } else {
                        // reverse the change to the grid
                        flip(i, j, it->second, grid);
                    }
                }
                // check if the rectangle is a square
                // if both length and height are the same
                if ((it->second).length != (it->second).height) {
                    // need to check rotation if not the same
                    // if the normal oriented rectangle does not work
                    // orient the rectange and check if solution exists
                    orient(it->second);
                    if (isValidPlace(i, j, length, height, it->second, grid)) {
                        // change the grid with correpsonding place
                        flip(i, j, it->second, grid);
                        // create a copy of it, so increment the copy will now change it
                        InputMapType::iterator itCopy = it;
                        // recursive call hasValidSolutions
                        // check if the rest of input triangles could be placed
                        if (hasValidSolutions(++itCopy, input, length, height, grid, output)) {
                            output.insert(make_pair(it->first, make_pair(i, j)));
                            // Found Solution!
                            return true;
                        } else {
                            // reverse the change to the grid
                            flip(i, j, it->second, grid);
                            // reorient the rectangle, change it back to the previous form
                            orient(it->second);
                        }
                    }
                }
                // go to next possible place
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool>> grid;

    for (int i = 0; i < n; i++) {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here
    solution_exists = hasValidSolutions(it, input, n, m, grid, output);

    if (!solution_exists) {
        ofile << "No solution found.";
    } else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}