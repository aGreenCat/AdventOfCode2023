#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool smudgeEqual(long int a, long int b) {
    return ((a ^ b) & ((a ^ b) - 1)) == 0;
}

int main() {
    ifstream fin("input.txt");

    int summary = 0;

    vector<vector<bool>> grid;

    string s;
    while (getline(fin, s)) {
        if (s.empty()) {
            int height = grid.size();
            int width = grid[0].size();
            cout << "size: " << height << " X " << width << endl; 

            // for (auto i : grid) {
            //     for (auto j : i) {
            //         if (j) cout << "1";
            //         else cout << " ";
            //     }
            //     cout << endl;
            // }

            long int rows[height];
            for (int r = 0; r < height; r++) {
                rows[r] = 0;
                int bitplace = 1;
                for (int c = 0; c < width; c++) {
                    if (grid[r][c]) rows[r] |= bitplace;
                    bitplace *= 2;
                }
            }
        
            // cout << endl << "ROWS: " << endl;
            // for (auto row : rows) {
            //     cout << row << endl;
            // }

            long int cols[width];
            for (int c = 0; c < width; c++) {
                cols[c] = 0;
                int bitplace = 1;
                for (int r = 0; r < height; r++) {
                    if (grid[r][c]) cols[c] |= bitplace;
                    bitplace *= 2;
                }
            }

            // cout << endl << "COLS: " << endl;
            // for (auto col : cols) {
            //     cout << col << endl;
            // }
            bool foundMirr = false;

            for (int c = 1; c < width; c++) {
                int mirr = -1;
                bool smudge;

                if (cols[c] == cols[c-1] || smudgeEqual(cols[c], cols[c-1])) {
                    mirr = c-1;
                    smudge = cols[c] != cols[c-1];
                }

                if (mirr == -1) continue;

                // cout << "mirr: " << mirr << " stop: " << min(mirr+1, width-(mirr+1)) << endl;

                for (int i = 1; i < min(mirr+1, width-(mirr+1)); i++) {
                    if (cols[mirr-i] != cols[mirr+i+1]) {
                        if (!smudge && smudgeEqual(cols[mirr-i], cols[mirr+i+1])) {
                            smudge = true;
                        } else {
                            mirr = -1;
                        }
                    }

                    // cout << "final mirr: " << mirr << endl;
                }


                if (mirr != -1 && smudge) {
                    cout << "col mirr: " << mirr << endl;
                    summary += mirr + 1;
                    
                    foundMirr = true;
                    break;
                } 
            }

            if (foundMirr) {
                grid.clear();
                continue;
            }

            for (int r = 1; r < height; r++) {
                int mirr = -1;
                bool smudge;

                if (rows[r] == rows[r-1] || smudgeEqual(rows[r], rows[r-1])) {
                    mirr = r-1;
                    smudge = rows[r] != rows[r-1];
                }

                if (mirr == -1) continue;

                for (int i = 1; i < min(mirr+1, height-(mirr+1)); i++) {
                    if (rows[mirr-i] != rows[mirr+i+1]) {
                        if (!smudge && smudgeEqual(rows[mirr-i], rows[mirr+i+1])) {
                            smudge = true;
                        } else {
                            mirr = -1;
                        }
                    }
                }

                if (mirr != -1 && smudge) {
                    cout << "row mirr: " << mirr << endl;
                    summary += 100 * (mirr + 1);

                    foundMirr = true;
                    break;
                }
            }

            if (foundMirr) {
                grid.clear();
                continue;
            }
            
            cout << "wtf" << endl;
            exit(1);
        } else {
            vector<bool> v;
            for (int i = 0; i < s.size(); i++) 
                v.push_back(s[i] == '#');

            grid.push_back(v);
        }
    }

    cout << summary << endl;

    return 0;
}