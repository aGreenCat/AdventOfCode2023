#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <climits>
#include <iomanip>
#include <string>
using namespace std;

const int GRID_WIDTH = 141;
const int GRID_HEIGHT = 141;
const int MIN_STEPS = 4;
const int MAX_STEPS = 10;

enum dir {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = 4
};

struct Node {
    int r;
    int c;
    dir d;
    int s;
    int dist;

    Node() {
        this->r = -1;
        this->c = -1;
        this->d = NONE;
        this->s = -1;
        this->dist = INT_MAX;
    }

    Node(int r, int c, dir d, int s) {
        this->r = r;
        this->c = c;
        this->d = d;
        this->s = s;
        this->dist = INT_MAX;
    }

    Node(int r, int c, dir d, int s, int dist) {
        this->r = r;
        this->c = c;
        this->d = d;
        this->s = s;
        this->dist = dist;
    }

    bool operator==(const Node& n) const {
        return r == n.r && c == n.c && d == n.d && s == n.s;
    }

    void setDist(int dist) {
        this->dist = dist;
    }

    string to_string() {
        return std::to_string(r) + " " + std::to_string(c) + " " + std::to_string(d) + " " + std::to_string(s) + " " + std::to_string(dist);
    }

    Node* getAdjacent(dir d) {
        if (r == 0 && d == UP) return nullptr;
        if (r == GRID_HEIGHT-1 && d == DOWN) return nullptr;
        if (c == 0 && d == LEFT) return nullptr;
        if (c == GRID_WIDTH-1 && d == RIGHT) return nullptr;

        
        if (s == MAX_STEPS-1 && this->d == d) return nullptr;

        if (s < MIN_STEPS-1) {
            if (d != this->d) {
                return nullptr;
            } else if (d == UP && r < MIN_STEPS) {
                return nullptr;
            } else if (d == DOWN && r >= GRID_HEIGHT-MIN_STEPS) {
                return nullptr;
            } else if (d == LEFT && c < MIN_STEPS) {
                return nullptr;
            } else if (d == RIGHT && c >= GRID_WIDTH-MIN_STEPS) {
                return nullptr;
            } else {
                Node* n;
                if (d == UP) n = new Node{r-1, c, d, this->d == UP ? s+1 : 0};
                if (d == DOWN) n = new Node{r+1, c, d, this->d == DOWN ? s+1 : 0};
                if (d == LEFT) n = new Node{r, c-1, d, this->d == LEFT ? s+1 : 0};
                if (d == RIGHT) n = new Node{r, c+1, d, this->d == RIGHT ? s+1 : 0};
                return n;
            }
        }

        if (d == UP) {
            return new Node{r-1, c, d, this->d == UP ? s+1 : 0};
        }
        if (d == DOWN) {
            return new Node{r+1, c, d, this->d == DOWN ? s+1 : 0};
        }
        if (d == LEFT) {
            return new Node{r, c-1, d, this->d == LEFT ? s+1 : 0};
        }
        if (d == RIGHT) {
            return new Node{r, c+1, d, this->d == RIGHT ? s+1 : 0};
        }
        return nullptr;
    }

};

class HashNode {

    public:
        size_t operator() (const Node& n) const {
            return hash<int>()(n.r) ^ hash<int>()(n.c) ^ hash<int>()(n.d) ^ hash<int>()(n.s);
        }
};

class Compare {
    public:
        bool operator()(Node* a, Node* b) {
            return a->dist > b->dist;
        }
};

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


    //setup dijkstras
    unordered_set<Node, HashNode> visited;
    priority_queue<Node*, vector<Node*>, Compare> adjs;


    Node initR(0, 1, RIGHT, 0, heat_loss[0][1]);
    adjs.push(&initR);
    Node initD(1, 0, DOWN, 0, heat_loss[1][0]);
    adjs.push(&initD);

    int lowestHeatLoss = INT_MAX;

    int count = 0;
    int lastHeatLoss = 0;
    while (!adjs.empty()) {
        Node* current = adjs.top();
        adjs.pop();

        //cout << "Current Node: " << current->to_string() << endl;

        if (visited.count(*current)) {
            //cout << "Already visited: " << current->to_string() << endl;
            continue;
        }

        for (dir d : {UP, DOWN, LEFT, RIGHT}) {
            if ((1 - (current->d)%2) + (current->d / 2) * 2 == d) continue;

            Node* adj = current->getAdjacent(d);
            if (adj != nullptr) {
                // cout << "adj: " << adj->to_string() << endl;
                if (!visited.count(*adj)) {
                    adj->setDist(current->dist + heat_loss[adj->r][adj->c]);
                    adjs.push(adj);
                    //cout << "Added: " << adj->to_string() << endl;
                } else {
                    //cout << "Don't add visited: " << adj->to_string() << endl;
                    delete adj;
                    adj == nullptr;
                }
            } else {
                //cout << "adj is null: " << d << endl;
            }
        }

        if (current->r == GRID_HEIGHT-1 && current->c == GRID_WIDTH-1 && current->s >= MIN_STEPS-1) {
            lowestHeatLoss = current->dist;
            break;
        }

        if (current->dist > lastHeatLoss) {
            lastHeatLoss = current->dist;
            cout << "Last heat loss: " << lastHeatLoss << endl;
        }

        visited.insert(*current);
        // if (count++ > 10) break;
    }

    cout << lowestHeatLoss << endl;

    return 0;
}