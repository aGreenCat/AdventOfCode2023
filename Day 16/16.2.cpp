#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
using namespace std;

const int GRID_WIDTH = 110;
const int GRID_HEIGHT = 110;

enum dir {UP, DOWN, LEFT, RIGHT};

unordered_set<string> cache;

void step(int& r, int& c, dir d) {
    switch (d) {
        case UP: 
            r--;
            break;
        case DOWN: 
            r++;
            break;
        case LEFT: 
            c--;
            break;
        case RIGHT: 
            c++;
            break;
    }
}

void beam(char grid[GRID_HEIGHT][GRID_WIDTH], bool energized[GRID_HEIGHT][GRID_WIDTH], int r, int c, dir d) {
    if (cache.find(to_string(r) + to_string(c) + to_string(d)) != cache.end())
        return;
    else 
        cache.insert(to_string(r) + to_string(c) + to_string(d));
    

    do {
        step(r, c, d);

        if (r < 0 || r >= GRID_HEIGHT || c < 0 || c >= GRID_WIDTH) 
            return;
        
        energized[r][c] = true;
    } while (grid[r][c] == '.');

    switch (grid[r][c]) {
        case '|':
            if (d == UP || d == DOWN) {
                beam(grid, energized, r, c, d);
            } else {
                beam(grid, energized, r, c, UP);
                beam(grid, energized, r, c, DOWN);
            }
            break;
        case '-':
            if (d == LEFT || d == RIGHT) {
                beam(grid, energized, r, c, d);
            } else {
                beam(grid, energized, r, c, LEFT);
                beam(grid, energized, r, c, RIGHT);
            }
            break;
        case '/':
            switch (d) {
                case UP: 
                    beam(grid, energized, r, c, RIGHT);
                    break;
                case DOWN: 
                    beam(grid, energized, r, c, LEFT);
                    break;
                case LEFT:
                    beam(grid, energized, r, c, DOWN);
                    break;
                case RIGHT:
                    beam(grid, energized, r, c, UP);
                    break;
            }
            break;
        case '\\':
            switch (d) {
                case UP: 
                    beam(grid, energized, r, c, LEFT);
                    break;
                case DOWN: 
                    beam(grid, energized, r, c, RIGHT);
                    break;
                case LEFT: 
                    beam(grid, energized, r, c, UP);
                    break;
                case RIGHT:
                    beam(grid, energized, r, c, DOWN);
                    break;
            }
            break;
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

    //print grid
    // for (int r = 0; r < GRID_HEIGHT; r++) {
    //     for (int c = 0; c < GRID_WIDTH; c++) {
    //         cout << grid[r][c] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    int maxEnergized = 0;

    for (int i = 0; i < GRID_HEIGHT; i++) {
        bool energized[GRID_HEIGHT][GRID_WIDTH];
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                energized[r][c] = false;

        beam(grid, energized, i, -1, RIGHT);
        
        //count number of energized tiles
        int numEnergized = 0;
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                numEnergized += energized[r][c];
        
        maxEnergized = max(maxEnergized, numEnergized);

        cache.clear();
    }
    for (int i = 0; i < GRID_HEIGHT; i++) {
        bool energized[GRID_HEIGHT][GRID_WIDTH];
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                energized[r][c] = false;

        beam(grid, energized, i, GRID_WIDTH, LEFT);
        
        //count number of energized tiles
        int numEnergized = 0;
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                numEnergized += energized[r][c];
        
        maxEnergized = max(maxEnergized, numEnergized);

        cache.clear();
    }
    for (int i = 0; i < GRID_WIDTH; i++) {
        bool energized[GRID_HEIGHT][GRID_WIDTH];
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                energized[r][c] = false;

        beam(grid, energized, -1, i, DOWN);
        
        //count number of energized tiles
        int numEnergized = 0;
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                numEnergized += energized[r][c];
        
        maxEnergized = max(maxEnergized, numEnergized);

        cache.clear();
    }
    for (int i = 0; i < GRID_WIDTH; i++) {
        bool energized[GRID_HEIGHT][GRID_WIDTH];
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                energized[r][c] = false;

        beam(grid, energized, GRID_HEIGHT, i, UP);
        
        //count number of energized tiles
        int numEnergized = 0;
        for (int r = 0; r < GRID_HEIGHT; r++)
            for (int c = 0; c < GRID_WIDTH; c++)
                numEnergized += energized[r][c];
        
        maxEnergized = max(maxEnergized, numEnergized);

        cache.clear();
    }

    cout << maxEnergized << endl;

    return 0;
}