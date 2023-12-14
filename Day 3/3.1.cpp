#include <iostream>
#include <fstream>
#include <string>
using namespace std;


bool adjacentToSymbol(int row, int start, int end, string schematic[140]) {
    if (row != 0) {
        for (int c = start; c < end; c++) {
            if (schematic[row-1][c] != '.' && !isdigit(schematic[row-1][c])) {
                return true;
            }
        }
    }

    if (row != 139) {
        for (int c = start; c < end; c++) {
            if (schematic[row+1][c] != '.' && !isdigit(schematic[row+1][c])) {
                return true;
            }
        }
    }

    if (start != 0) {
        for (int r = max(0, row-1); r < min(140, row+2); r++) {
            if (schematic[r][start-1] != '.' && !isdigit(schematic[r][start-1])) {
                return true;
            }
        }
    }

    if (end != schematic[0].size()) {
        for (int r = max(0, row-1); r < min(140, row+2); r++) {
            if (schematic[r][end] != '.' && !isdigit(schematic[r][end])) {
                return true;
            }
        }
    }

    return false;
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
        string row = schematic[r];

        int start = 0;
        int end = 0;

        while (end < row.size()) {
            if (isdigit(row[start])) {
                end++;
                if (!isdigit(row[end])) {
                    int num = stoi(row.substr(start, end-start));
                    if (adjacentToSymbol(r, start, end, schematic)) {
                        cout << "yay: " << num << endl;
                        sum += num;
                    } else {
                        cout << "nay: " << num << endl;
                    }

                    start = end;
                }
            } else {
                start++;
                end++;
            }
        }
        
    }

    cout << sum;

    return 0;
}