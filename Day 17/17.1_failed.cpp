#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <climits>
#include <iomanip>
using namespace std;

const int GRID_WIDTH = 13;
const int GRID_HEIGHT = 13;

enum dir {UP, DOWN, LEFT, RIGHT, NONE};

class Block {
    public:
        Block(int r, int c, int loss) : r(r), c(c), loss(loss), pathLoss(INT_MAX), d(NONE), consecutive(0) {}
        Block() : r(0), c(0), loss(0), pathLoss(INT_MAX), d(NONE), consecutive(0) {}

        int getRow() const { return r; }
        int getCol() const { return c; }
        int getLoss() const { return loss; }
        int getPathLoss() const { return pathLoss; }
        dir getDir() const { return d; }
        int getConsecutive() const { return consecutive; }

        void setDir(dir d) { this->d = d; }
        void setPathLoss(int p) { pathLoss = p; }
        void updateConsecutive(int c) { consecutive = c+1; }
        void updatePathLoss(int p) { pathLoss = p + this->loss; }

        void print() {
            cout << "Block: " << "r: " << r << " c: " << c << " loss: " << loss << " pathLoss: " << pathLoss << " d: " << d << " consecutive: " << consecutive << endl;
        }
        
        Block* getAbove(Block grid[GRID_HEIGHT][GRID_WIDTH]) const {
            if (r == 0 || (consecutive >= 3 && d == UP)) {
                return nullptr;
            } 

            return &grid[r-1][c];
        }
        Block* getBelow(Block grid[GRID_HEIGHT][GRID_WIDTH]) const {
            if (r == GRID_HEIGHT-1 || (consecutive >= 3 && d == DOWN)) {
                return nullptr;
            } 

            return &grid[r+1][c];
        }
        Block* getLeft(Block grid[GRID_HEIGHT][GRID_WIDTH]) const {
            if (c == 0 || (consecutive >= 3 && d == LEFT)) {
                return nullptr;
            } 

            return &grid[r][c-1];
        }
        Block* getRight(Block grid[GRID_HEIGHT][GRID_WIDTH]) const {
            if (c == GRID_WIDTH-1 || (consecutive >= 3 && d == RIGHT)) {
                return nullptr;
            } 

            return &grid[r][c+1];
        }

        char getPrintDir() const {
            if (d == UP) {
                return '^';
            } else if (d == DOWN) {
                return 'v';
            } else if (d == LEFT) {
                return '<';
            } else if (d == RIGHT) {
                return '>';
            } else {
                return ' ';
            }
        }

    private:
        int r;
        int c;
        int loss;
        int pathLoss;
        dir d;
        int consecutive;
};

//Custom comparator for priority queue of Block pointers
class Compare {
    public:
        bool operator()(Block* a, Block* b) {
            // if (a->getPathLoss() > b->getPathLoss()) {
            //     return true;
            // }

            // return a->getConsecutive() < b->getConsecutive();

            return a->getPathLoss() > b->getPathLoss();
        }
};

Block grid[GRID_HEIGHT][GRID_WIDTH];

int main() {
    //Parse input
    ifstream fin("input.txt");

    string s;
    for (int r = 0; r < GRID_HEIGHT; r++) {
        getline(fin, s);
        for (int c = 0; c < GRID_WIDTH; c++) {
            grid[r][c] = {r, c, s[c]-'0'};
        }
    }

    fin.close();

    set<Block*> visited;
    priority_queue<Block*, vector<Block*>, Compare> adj;

    grid[0][0].setPathLoss(0);
    Block* lastAdded = &grid[0][0];
    visited.insert(lastAdded);

    int count = 0;

    while (!visited.count(&grid[GRID_HEIGHT-1][GRID_WIDTH-1])) {
        Block* b = lastAdded;
        
        
        Block* adj_block;

        adj_block = b->getAbove(grid);
        if (adj_block != nullptr && !visited.count(adj_block)) {
            if (b->getPathLoss() + adj_block->getLoss() <= adj_block->getPathLoss()) {
                if (b->getPathLoss() + adj_block->getLoss() == adj_block->getPathLoss()) {
                    if (b->getDir() != UP) {
                        adj_block->setDir(UP);
                        adj_block->updateConsecutive(0);
                    }
                } else {
                    adj_block->updatePathLoss(b->getPathLoss());
                    adj_block->setDir(UP);

                    if (b->getDir() == UP) {
                        adj_block->updateConsecutive(b->getConsecutive());
                    } else {
                        adj_block->updateConsecutive(0);
                    }

                    adj.push(adj_block);
                }
            }
        }
        
        adj_block = b->getBelow(grid);
        if (adj_block != nullptr && !visited.count(adj_block)) {
            
            if (b->getPathLoss() + adj_block->getLoss() <= adj_block->getPathLoss()) {
                if (b->getPathLoss() + adj_block->getLoss() == adj_block->getPathLoss()) {
                    if (adj_block->getRow()==1 && adj_block->getCol()==2) {
                        cout << "found: " << adj_block->getPathLoss() << endl;
                    }
                    if (b->getDir() != DOWN) {
                        adj_block->setDir(DOWN);
                        adj_block->updateConsecutive(0);
                    }
                } else {
                    adj_block->updatePathLoss(b->getPathLoss());
                    adj_block->setDir(DOWN);

                    if (b->getDir() == DOWN) {
                        adj_block->updateConsecutive(b->getConsecutive());
                    } else {
                        adj_block->updateConsecutive(0);
                    }

                    adj.push(adj_block);
                }
            }
        }
        adj_block = b->getLeft(grid);
        if (adj_block != nullptr && !visited.count(adj_block)) {

            if (b->getPathLoss() + adj_block->getLoss() <= adj_block->getPathLoss()) {
                if (b->getPathLoss() + adj_block->getLoss() == adj_block->getPathLoss()) {
                    if (b->getDir() != LEFT) {
                        adj_block->setDir(LEFT);
                        adj_block->updateConsecutive(0);
                    }
                } else {
                    adj_block->updatePathLoss(b->getPathLoss());
                    adj_block->setDir(LEFT);

                    if (b->getDir() == LEFT) {
                        adj_block->updateConsecutive(b->getConsecutive());
                    } else {
                        adj_block->updateConsecutive(0);
                    }

                    adj.push(adj_block);
                }
            }
        }
        adj_block = b->getRight(grid);
        if (adj_block != nullptr && !visited.count(adj_block)) {
            if (b->getPathLoss() + adj_block->getLoss() <= adj_block->getPathLoss()) {
                if (b->getPathLoss() + adj_block->getLoss() == adj_block->getPathLoss()) {
                    if (adj_block->getRow()==1 && adj_block->getCol()==2) {
                        cout << "found: " << adj_block->getPathLoss() << endl;
                    }
                    if (b->getDir() != RIGHT) {
                        adj_block->setDir(RIGHT);
                        adj_block->updateConsecutive(0);
                    }
                } else {
                    adj_block->updatePathLoss(b->getPathLoss());
                    adj_block->setDir(RIGHT);

                    if (b->getDir() == RIGHT) {
                        adj_block->updateConsecutive(b->getConsecutive());
                    } else {
                        adj_block->updateConsecutive(0);
                    }

                    adj.push(adj_block);
                }
            }
        }

        // cout << "adj size: " << adj.size() << endl;


        // //print visited
            // auto it = visited.begin();
            // while (it != visited.end()) {
            //     cout << "visited: " << (*it)->getRow() << ", " << (*it)->getCol() << endl;
            //     it++;
            // }

        //pass on duplicates
        while (!adj.empty() && visited.count(adj.top())) {
            // cout << "popped duplicate: ";
            // adj.top()->print();
            adj.pop();
        }

        lastAdded = adj.top();
        visited.insert(adj.top());
        adj.top()->print();

        adj.pop();

        // if (count++ == 10) {
        //     break;
        // }
    }

    // //print priority queue
    // cout << "adj size: " << adj.size() << endl;
    // while (!adj.empty()) {
    //     adj.top()->print();
    //     adj.pop();
    // }

    for (int r = 0; r < GRID_HEIGHT; r++) {
        for (int c = 0; c < GRID_WIDTH; c++) {
            cout << setw(4) << grid[r][c].getPrintDir() << " ";
            // cout << setw(4) << grid[r][c].getConsecutive() << " ";

        }
        cout << endl;
    }
    

    cout << grid[GRID_HEIGHT-1][GRID_WIDTH-1].getPathLoss() << endl;

    return 0;
}