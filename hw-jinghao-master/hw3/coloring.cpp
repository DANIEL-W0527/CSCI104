#include <fstream>
#include <iostream>

using namespace std;

// Functions Prototypes
int** getNeighborMatrix(char** countriesMap, int countriesNum, int rows, int columns);
bool checkColors(int** neighborsMatrix, int* colorAssignments, int countriesNum);
bool assignColors(int** neighborsMatrix, int countriesNum, int countryIndex, int* colorAssignments, int colorNumbers);

int main(int argc, char* argv[]) {
    // check if an input file is given
    if (argc < 2) {
        cout << "Please specify an input file." << endl;
        return 1;
    }

    // check if the input file is valid
    ifstream ifile(argv[1]);
    if (ifile.fail()) {
        cout << "Could not open the file." << endl;
        return 1;
    }

    // get number of countries, rows, and columns
    int countriesNum;
    int rows;
    int columns;
    ifile >> countriesNum;
    ifile >> rows;
    ifile >> columns;

    // store the given map
    char** countriesMap = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        countriesMap[i] = new char[columns];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            char tempChar;
            ifile >> tempChar;
            countriesMap[i][j] = tempChar;
        }
    }

    // close the ifile
    ifile.close();

    // generate the corresponding neighborsMatrix colorAssignment array
    int** neighborsMatrix = getNeighborMatrix(countriesMap, countriesNum, rows, columns);
    // create a colorAssignment array of all countries and intialize them with 0
    // index 0 corresponding to country A's color, index 1 corresponding to country B's color, ...
    int* colorAssignment = new int[countriesNum];
    for (int i = 0; i < countriesNum; ++i) {
        colorAssignment[i] = 0;
    }

    // check if the coloring exists
    // if exists, print out the color assignment
    if (assignColors(neighborsMatrix, countriesNum, 0, colorAssignment, 4)) {
        for (int i = 0; i < countriesNum; ++i) {
            cout << char(i + 65) << " " << colorAssignment[i] << endl;
        }
    }
    // else print out the failure message
    else {
        cout << "The graph coloring does not exist." << endl;
    }

    // deallocate the memory of countriesMap
    for (int i = 0; i < rows; ++i) {
        delete[] countriesMap[i];
    }
    delete[] countriesMap;

    // deallocate the memory of neighborsMatrix
    for (int i = 0; i < countriesNum; ++i) {
        delete[] neighborsMatrix[i];
    }
    delete[] neighborsMatrix;

    // deallocate the memory of colorAssignment
    delete[] colorAssignment;
}

/* create a neighborhood matrix:
 * row: 0 represents A, 1 represents B, 2 represents C,...
 * col: 0 represents A, 1 represents B, 2 represents C,...
 * Value:
 * 0 reprsenting two countries are not adjacent for all points in the map
 * 1 representing two countries are adjacent at some point in the map
 */
int** getNeighborMatrix(char** countriesMap, int countriesNum, int rows, int columns) {
    // create an empty countriesNum * countriesNum martix
    int** adjMatrix = new int*[countriesNum];
    for (int i = 0; i < countriesNum; ++i) {
        adjMatrix[i] = new int[countriesNum];
    }
    for (int i = 0; i < countriesNum; ++i) {
        for (int j = 0; j < countriesNum; ++j) {
            adjMatrix[i][j] = 0;
        }
    }
    // go through all the points in map and check their neigbors
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // if the point has same value as country, check its neighbors
            // top neighbor if exists
            if (i - 1 >= 0 && i - 1 < rows) {
                // get index in adjMatrix
                int index1 = (int)(countriesMap[i][j]) - 65;
                int index2 = (int)(countriesMap[i - 1][j]) - 65;
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index1][index2] == 0) {
                    adjMatrix[index1][index2] = 1;
                }
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index2][index1] == 0) {
                    adjMatrix[index2][index1] = 1;
                }
            }
            // bottom neighbor if exists
            if (i + 1 >= 0 && i + 1 < rows) {
                // get index in adjMatrix
                int index1 = (int)(countriesMap[i][j]) - 65;
                int index2 = (int)(countriesMap[i + 1][j]) - 65;
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index1][index2] == 0) {
                    adjMatrix[index1][index2] = 1;
                }
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index2][index1] == 0) {
                    adjMatrix[index2][index1] = 1;
                }
            }
            // left neighbor if exists
            if (j - 1 >= 0 && j - 1 < columns) {
                // get index in adjMatrix
                int index1 = (int)(countriesMap[i][j]) - 65;
                int index2 = (int)(countriesMap[i][j - 1]) - 65;
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index1][index2] == 0) {
                    adjMatrix[index1][index2] = 1;
                }
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index2][index1] == 0) {
                    adjMatrix[index2][index1] = 1;
                }
            }
            // right neighbor if exists
            if (j + 1 >= 0 && j + 1 < columns) {
                // get index in adjMatrix
                int index1 = (int)(countriesMap[i][j]) - 65;
                int index2 = (int)(countriesMap[i][j + 1]) - 65;
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index1][index2] == 0) {
                    adjMatrix[index1][index2] = 1;
                }
                // if the edges between two countries does not exist in adjMatrix, change to 1
                if (adjMatrix[index2][index1] == 0) {
                    adjMatrix[index2][index1] = 1;
                }
            }
        }
    }
    return adjMatrix;
}

// check if the specific color Assignment is valid
bool checkColors(int** neighborsMatrix, int* colorAssignments, int countriesNum) {
    // Since the neigbors Matrix is symmetric, we choose to check left bottom part of the matrix
    for (int i = 0; i < countriesNum; ++i) {
        for (int j = i + 1; j < countriesNum; ++j) {
            // if two countries are adjacent at some point in map and
            // the color assignment for two countries are the same
            // it means the color assignment is invalid
            if (neighborsMatrix[i][j] == 1 && colorAssignments[i] == colorAssignments[j]) {
                return false;
            }
        }
    }
    // otherwise, color assignment is valid
    return true;
}

// assign color to each countries
// country Index: 0 for A, 1 for B, 2 for C,...
bool assignColors(int** neighborsMatrix, int countriesNum, int countryIndex, int* colorAssignments, int colorNumbers) {
    // if there is no countries needed to be assigned,
    // check if current assignment is valid
    if (countryIndex == countriesNum) {
        // if valid, we found the correct color assignment
        if (checkColors(neighborsMatrix, colorAssignments, countriesNum)) {
            return true;
        }
        // if not valid, there doesn't exist possible color assignment
        return false;
    }

    // if there is country waiting to be assigned
    else {
        // loop through all possible color assignments for the coutry of country Index
        for (int i = 1; i <= colorNumbers; ++i) {
            colorAssignments[countryIndex] = i;
            // use recursion to find if the countries waiting to be assigned color have valid coloring
            // if countries waiting to be assigned color have valid coloring, we found the correct coloring
            if (assignColors(neighborsMatrix, countriesNum, countryIndex + 1, colorAssignments, colorNumbers)) {
                return true;
            }
            // if countries waiting to be assigned color do not have valid coloring,
            // we change the color for the country of country Indedx back to 0;
            colorAssignments[countryIndex] = 0;
        }
        // if all coloring options did not work, there doesn't exist such coloring
        return false;
    }
}