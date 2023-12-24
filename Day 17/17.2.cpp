#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <string>

const size_t WIDTH = 141;
const size_t HEIGHT = 141;

const size_t MAX_STRAIGHT = 10;
const size_t MIN_TURN = 4;

enum dir {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};

struct pos {
    static pos unit_pos(dir d) {
        if (d == UP) return {-1, 0};
        if (d == DOWN) return {1, 0};
        if (d == LEFT) return {0, -1};
        if (d == RIGHT) return {0, 1};

        return {0, 0};
    }

    int r;
    int c;

    pos rotateLeft() {
        return {-c, r};
    }

    pos rotateRight() {
        return {c, -r};
    }

    pos operator+(const pos& other) const {return {r+other.r, c+other.c};}
    bool operator==(const pos& other) const {return r == other.r && c == other.c;}
};

struct move {
    pos p;
    dir d;
    size_t steps;
    size_t loss;

    bool operator<(const move& other) const {return loss > other.loss;}
    bool operator==(const move& other) const {return p == other.p && d == other.d && steps == other.steps;}
};

struct hash_move {
    size_t operator()(const move& m) const {
        return m.p.r*HEIGHT*WIDTH*40 + m.p.c*WIDTH*40 + m.d*40 + m.steps;
    }
};

class heat_grid {
    public:
        size_t grid[HEIGHT][WIDTH];

        heat_grid(const std::string& file) {
            std::ifstream fs(file);
            std::string line;
            for (size_t r = 0; r < HEIGHT; r++) {
                std::getline(fs, line);
                for (size_t c = 0; c < WIDTH; c++) {
                    grid[r][c] = line[c] - '0';
                }
            }
        }

        size_t get(pos p) const {
            return grid[p.r][p.c];
        }

        bool in_bounds(pos p) const {
            return p.r >= 0 && p.r < HEIGHT && p.c >= 0 && p.c < WIDTH;
        }
};


int main() {
    heat_grid hg("input.txt");

    std::unordered_set<move, hash_move> visited;
    std::priority_queue<move> adjs;

    adjs.push({{0, 1}, RIGHT, 1, hg.get({0, 1})});
    adjs.push({{1, 0}, DOWN, 1, hg.get({1, 0})});

    while (!adjs.empty()) {
        move curr = adjs.top();
        adjs.pop();

        //std::cout << curr.p.r << " " << curr.p.c << " " << curr.d << " " << curr.steps << " " << curr.loss << std::endl;

        if (visited.count(curr)) {
            continue;
        }

        visited.insert(curr);

        if (curr.steps >= MIN_TURN) {
            pos offset = pos::unit_pos(curr.d).rotateLeft();
            pos adj_pos = curr.p + offset;
            if (hg.in_bounds(adj_pos)) {
                move adj = {adj_pos, dir((curr.d + 1)%4), 1, curr.loss + hg.get(adj_pos)};
                adjs.push(adj);
            }
        }

        if (curr.steps >= MIN_TURN) {
            pos offset = pos::unit_pos(curr.d).rotateRight();
            pos adj_pos = curr.p + offset;
            if (hg.in_bounds(adj_pos)) {
                move adj = {adj_pos, dir((curr.d + 3)%4), 1, curr.loss + hg.get(adj_pos)};
                adjs.push(adj);
            }
        }

        if (curr.steps < MAX_STRAIGHT) {
            pos offset = pos::unit_pos(curr.d);
            pos adj_pos = curr.p + offset;
            if (hg.in_bounds(adj_pos)) {
                move adj = {adj_pos, curr.d, curr.steps + 1, curr.loss + hg.get(adj_pos)};
                adjs.push(adj);
            }
        }

        if (curr.p == pos{HEIGHT-1, WIDTH-1} && curr.steps >= MIN_TURN) {
            std::cout << "Least heat loss: " << curr.loss << std::endl;
            break;
        }
    }

    return 0;
}