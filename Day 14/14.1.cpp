#include <iostream>
#include <fstream>
using namespace std;

int GRID_WIDTH = 100;
int GRID_HEIGHT = 100;

int main() {
    char grid[GRID_HEIGHT][GRID_WIDTH];

    ifstream fin("input.txt");

    string s;
    for (int r = 0; r < GRID_HEIGHT; r++) {
        getline(fin, s);

        for (int c = 0; c < GRID_WIDTH; c++) {
            grid[r][c] = s[c];
        }
    }

    fin.close();


    int load = 0;
    for (int c = 0; c < GRID_WIDTH; c++) {
        int anchor = -1;

        for (int r = 0; r < GRID_HEIGHT; r++) {
            if (grid[r][c] == '#')
                anchor = r;
            
            if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[anchor+1][c] = 'O';

                anchor += 1;
                load += GRID_HEIGHT - anchor;
            }
        }
    }

    // for (int r = 0; r < GRID_HEIGHT; r++) {
    //     for (int c = 0; c < GRID_WIDTH; c++) {
    //         cout << grid[r][c];
    //     }
    //     cout << endl;
    // }
    
    cout << load;

    return 0;
}