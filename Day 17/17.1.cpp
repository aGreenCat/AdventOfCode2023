#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <climits>
#include <iomanip>
using namespace std;

const int GRID_WIDTH = 141;
const int GRID_HEIGHT = 141;

enum dir {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = 4
};

struct State {
    int r;
    int c;
    dir d;
    int s;
    int dist;


    State* getAdjacent(State grid[GRID_HEIGHT][GRID_WIDTH][4][3], dir d) {
        if (r == 0 && d == UP) return nullptr;
        if (r == GRID_HEIGHT-1 && d == DOWN) return nullptr;
        if (c == 0 && d == LEFT) return nullptr;
        if (c == GRID_WIDTH-1 && d == RIGHT) return nullptr;

        if (s == 2 && this->d == d) return nullptr;

        if (d == UP) return &grid[r-1][c][d][this->d == UP ? s+1 : 0];
        if (d == DOWN) return &grid[r+1][c][d][this->d == DOWN ? s+1 : 0];
        if (d == LEFT) return &grid[r][c-1][d][this->d == LEFT ? s+1 : 0];
        if (d == RIGHT) return &grid[r][c+1][d][this->d == RIGHT ? s+1 : 0];
        return nullptr;
    }

};

class Compare {
    public:
        bool operator()(State* a, State* b) {
            return a->dist > b->dist;
        }
};

State* getMin(int r, int c, State grid[GRID_HEIGHT][GRID_WIDTH][4][3]) {
    State* lowest = nullptr;
    int lowestDist = INT_MAX;

    for (int d = 0; d < 4; d++) {
        for (int s = 0; s < 3; s++) {
            if (grid[r][c][d][s].dist < lowestDist) {
                lowest = &grid[r][c][d][s];
                lowestDist = grid[r][c][d][s].dist;
            }
        }
    }

    return lowest;
}

int main() {
    //Parse input
    int heat_loss[GRID_HEIGHT][GRID_WIDTH];

    ifstream fin("input.txt");

    string s;
    for (int r = 0; r < GRID_HEIGHT; r++) {
        getline(fin, s);
        for (int c = 0; c < GRID_WIDTH; c++) {
            heat_loss[r][c] = s[c] - '0';
        }
    }

    fin.close();

    //populate grid
    State grid[GRID_HEIGHT][GRID_WIDTH][4][3];

    for (int r = 0; r < GRID_HEIGHT; r++) {
        for (int c = 0; c < GRID_WIDTH; c++) {
            for (int d = 0; d < 4; d++) {
                for (int s = 0; s < 3; s++) {
                    grid[r][c][d][s] = {r, c, (dir) d, s, INT_MAX};
                }
            }
        }
    }

    //setup dijkstras
    set<State*> visited;
    priority_queue<State*, vector<State*>, Compare> adjs;

    grid[0][1][RIGHT][0].dist = heat_loss[0][1];
    grid[1][0][DOWN][0].dist = heat_loss[1][0];
    adjs.push(&grid[0][1][RIGHT][0]);
    adjs.push(&grid[1][0][DOWN][0]);

    while (!adjs.empty()) {
        State* current = adjs.top();
        if (visited.find(current) != visited.end()) {
            cout << "Removed " << current->r << " " <<  current->c << " " << current->d << " " << current->s << " " << current->dist << endl;
            adjs.pop();
            continue;
        }

        //cout << current->r << " " << current->c << " " << current->d << " " << current->s << " " << current->dist << endl;

        for (dir d : {UP, DOWN, LEFT, RIGHT}) {
            if ((1 - (current->d)%2) + (current->d / 2) * 2 == d) continue;

            State* adj = current->getAdjacent(grid, d);
            if (adj != nullptr && adj->dist == INT_MAX) {
                adj->dist = current->dist + heat_loss[adj->r][adj->c];
                adjs.push(adj);
            }
        }

        visited.insert(current);
        adjs.pop();
    }

    int lowest = INT_MAX;
    for (int d = 0; d < 4; d++) {
        for (int s = 0; s < 3; s++) {
            lowest = min(grid[GRID_HEIGHT-1][GRID_WIDTH-1][d][s].dist, lowest);
        }
    }

    cout << lowest << endl;

    // //print grid
    // for (int r = 0; r < GRID_HEIGHT; r++) {
    //     for (int c = 0; c < GRID_WIDTH; c++) {
    //         cout << "row: " << r << " col: " << c << endl;
    //         for (int d = 0; d < 4; d++) {
    //             for (int s = 0; s < 3; s++) {
    //                 cout << setw(12) << grid[r][c][d][s].dist << " ";
    //             }
    //             cout << endl;
    //         }
    //         cout << endl;
    //     }
    // }

    return 0;
}