#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool numAdjPartsIsTwo(int row, int col, string schematic[140]) {
    int numParts = 0;
    
    if (col != 0) {
        if (isdigit(schematic[row][col-1])) {
            numParts++;
        }
    }

    if (col != schematic[0].size()-1) {
        if (isdigit(schematic[row][col+1])) {
            numParts++;
        }
    }

    if (row != 0) {
        if (isdigit(schematic[row-1][col])) {
            numParts++;
        } else {
            if (col != 0 && isdigit(schematic[row-1][col-1])) {
                numParts++;
            }
            if (col != schematic[0].size()-1 && isdigit(schematic[row-1][col+1])) {
                numParts++;
            }
        }
    }

    if (row != 139) {
        if (isdigit(schematic[row+1][col])) {
            numParts++;
        } else {
            if (col != 0 && isdigit(schematic[row+1][col-1])) {
                numParts++;
            }
            if (col != schematic[0].size()-1 && isdigit(schematic[row+1][col+1])) {
                numParts++;
            }
        }
    }

    return numParts == 2;
}

int findNum(int row, int col, string schematic[140]) {
    int start = col;
    int end = col;

    while (start > 0) {
        start--;
        if (!isdigit(schematic[row][start])) {
            start++;
            break;
        }
    }

    while (end < schematic[0].size()-1) {
        end++;
        if (!isdigit(schematic[row][end])) {
            break;
        }
    }

    return stoi(schematic[row].substr(start, end-start));
}

int findRatio(int row, int col, string schematic[140]) {
    int numParts = 0;
    int ratio = 1;

    if (col != 0) {
        if (isdigit(schematic[row][col-1])) {
            numParts++;
            ratio *= findNum(row, col-1, schematic);
        }
    }

    if (col != schematic[0].size()-1) {
        if (isdigit(schematic[row][col+1])) {
            numParts++;
            ratio *= findNum(row, col+1, schematic);
        }
    }

    if (row != 0) {
        if (isdigit(schematic[row-1][col])) {
            numParts++;
            ratio *= findNum(row-1, col, schematic);
        } else {
            if (col != 0 && isdigit(schematic[row-1][col-1])) {
                numParts++;
                ratio *= findNum(row-1, col-1, schematic);
            }
            if (col != schematic[0].size()-1 && isdigit(schematic[row-1][col+1])) {
                numParts++;
                ratio *= findNum(row-1, col+1, schematic);
            }
        }
    }

    if (row != 139) {
        if (isdigit(schematic[row+1][col])) {
            numParts++;
            ratio *= findNum(row+1, col, schematic);
        } else {
            if (col != 0 && isdigit(schematic[row+1][col-1])) {
                numParts++;
                ratio *= findNum(row+1, col-1, schematic);
            }
            if (col != schematic[0].size()-1 && isdigit(schematic[row+1][col+1])) {
                numParts++;
                ratio *= findNum(row+1, col+1, schematic);
            }
        }
    }

    return ratio;
}


int main() {
    ifstream fin("input.txt");

    string schematic[140];

    int i = 0;
    
    string s;
    while (getline(fin, s)) {
        schematic[i] = s;
        i++;
    }


    int sum = 0; 

    for (int r = 0; r < 140; r++) {
        for (int c = 0; c < schematic[0].size(); c++) {
            if (schematic[r][c] == '*') {
                if (numAdjPartsIsTwo(r, c, schematic)) {
                    int ratio = findRatio(r, c,schematic);
                    sum += ratio;
                }
            }
        }        
    }

    cout << sum;

    return 0;
}