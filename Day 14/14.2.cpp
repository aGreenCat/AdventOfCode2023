#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;

struct Stone {
    int r;
    int c;
};

void cycle(char grid[GRID_HEIGHT][GRID_WIDTH]) {
    vector<Stone> stones;

    for (int c = 0; c < GRID_WIDTH; c++) {
        int anchor = -1;

        for (int r = 0; r < GRID_HEIGHT; r++) {
            if (grid[r][c] == '#')
                anchor = r;
            
            if (grid[r][c] == 'O') {
                stones.push_back({r, c});

                grid[r][c] = '.';
                grid[anchor+1][c] = 'O';

                anchor += 1;
            }
        }
    }

    for (int r = 0; r < GRID_HEIGHT; r++) {
        int anchor = -1;
        for (int c = 0; c < GRID_WIDTH; c++) {
            if (grid[r][c] == '#')
                anchor = c;
            
            if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[r][anchor+1] = 'O';
                
                anchor += 1;
            }
        }
    }

    for (int c = 0; c < GRID_WIDTH; c++) {
        int anchor = GRID_HEIGHT;

        for (int r = GRID_HEIGHT-1; r >= 0; r--) {
            if (grid[r][c] == '#')
                anchor = r;
            
            if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[anchor-1][c] = 'O';

                anchor -= 1;
            }
        }
    }

    for (int r = 0; r < GRID_HEIGHT; r++) {
        int anchor = GRID_WIDTH;
        for (int c = GRID_WIDTH-1; c >= 0; c--) {
            if (grid[r][c] == '#')
                anchor = c;
            
            if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[r][anchor-1] = 'O';
                
                anchor -= 1;
            }
        }
    }
}


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

    unordered_map<string, int> all_changes;
    string changes;

    char prevGrid[GRID_HEIGHT][GRID_WIDTH];
    for (int i = 0; i < 117 + (1000000000-117) % 14; i++) {
        //copy grid
        for (int r = 0; r < GRID_HEIGHT; r++) {
            for (int c = 0; c < GRID_WIDTH; c++) {
                prevGrid[r][c] = grid[r][c];
            }
        }

        cycle(grid);

        // if (prevChange == changes) {
        //     break;
        // }

        changes = "";

        for (int r = 0; r < GRID_HEIGHT; r++) {
            for (int c = 0; c < GRID_WIDTH; c++) {
                if (grid[r][c] != prevGrid[r][c]) {
                    changes += prevGrid[r][c] == '.' ? 'x' : 'o';
                    changes += to_string(r) + to_string(c);
                }
            }
        }

        // cout << i << ": " << changes << endl;

        if (all_changes.find(changes) != all_changes.end()) {
            //cout << i << " is looped: " << i - all_changes[changes] << endl;
        }

        all_changes[changes] = i;
    }

    int load = 0;

    for (int r = 0; r < GRID_HEIGHT; r++) {
        for (int c = 0; c < GRID_WIDTH; c++) {
            if (grid[r][c] == 'O')
                load += GRID_HEIGHT - r;
        }
    }

    cout << load;

    return 0;
}