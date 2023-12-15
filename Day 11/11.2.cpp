#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <cmath>
using namespace std;

const int GRID_WIDTH = 140;
const int GRID_HEIGHT = 140;

const int EXPANSION = 999999;

struct Coord {
    int r;
    int c;
};

int main() {
    ifstream fin("input.txt");

    bool grid[GRID_HEIGHT][GRID_WIDTH];

    string s;
    for (int r = 0; r < GRID_HEIGHT; r++) {
        getline(fin, s);
        for (int c = 0; c < GRID_WIDTH; c++) {
            grid[r][c] = s[c] == '#';
        }
    }

    unordered_set<int> empty_rows;
    unordered_set<int> empty_cols;
    
    for (int r = 0; r < GRID_HEIGHT; r++) {
        bool empty = true;
        for (int c = 0; c < GRID_WIDTH; c++) {
            if (grid[r][c]) {
                empty = false;
                break;
            }
        }

        if (empty) empty_rows.insert(r);
    }

    for (int c = 0; c < GRID_WIDTH; c++) {
        bool empty = true;
        for (int r = 0; r < GRID_WIDTH; r++) {
            if (grid[r][c]) {
                empty = false;
                break;
            }
        }

        if (empty) empty_cols.insert(c);
    }

    // for (auto r : empty_rows) {
    //     cout << r << " ";
    // }
    // cout << endl << endl;
    // for (auto r : empty_cols) {
    //     cout << r << " ";
    // }

    vector<Coord> galaxy_coords;

    int r_offset = 0;
    for (int r = 0; r < GRID_HEIGHT; r++) {
        // If row is empty, add to offset and continue
        // There are no galaxies in an empty row
        if (empty_rows.find(r) != empty_rows.end()) {
            r_offset++;
            continue;
        }

        int c_offset = 0;
        for (int c = 0; c < GRID_WIDTH; c++) {
            if (empty_cols.find(c) != empty_cols.end()) {
                c_offset++;
                continue;
            }
            
            if (grid[r][c]) galaxy_coords.push_back(Coord{r + r_offset*EXPANSION, c + c_offset*EXPANSION});
        }
    }

    // for (Coord coord : galaxy_coords) {
    //     cout << coord.r << ", " << coord.c << endl;
    // }

    long long int total_dists = 0;

    for (int i = 0; i < galaxy_coords.size(); i++) {
        Coord first_coord = galaxy_coords[i];
        for (int j = i+1; j < galaxy_coords.size(); j++) {
            Coord second_coord = galaxy_coords[j];
            
            int man_dist = abs(first_coord.r - second_coord.r) + abs(first_coord.c - second_coord.c);
            total_dists += man_dist;
            //cout << total_dists << endl;
        }
    }

    cout << total_dists << endl;

    return 0;
}