#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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
            
            int mirrInd = -1;

            long int rows[height];
            for (int r = 0; r < height; r++) {
                rows[r] = 0;
                int bitplace = 1;
                for (int c = 0; c < width; c++) {
                    if (grid[r][c]) rows[r] |= bitplace;
                    bitplace *= 2;
                }

                if (mirrInd == -1) {
                    if (r != 0 && rows[r] == rows[r-1]) {
                        mirrInd = r-1;
                    }
                } else if (mirrInd - (r-(mirrInd+1)) >= 0 && rows[r] != rows[mirrInd - (r-(mirrInd+1))]) {
                    mirrInd = -1;
                }
            }

            if (mirrInd != -1) {
                summary += 100 * (mirrInd + 1);
                cout << "row mirrInd: " << mirrInd << endl;

                grid.clear();
                continue;
            }

            long int cols[width];
            for (int c = 0; c < width; c++) {
                cols[c] = 0;
                int bitplace = 1;
                for (int r = 0; r < height; r++) {
                    if (grid[r][c]) cols[c] |= bitplace;
                    bitplace *= 2;
                }

                if (mirrInd == -1) {
                    if (c != 0 && cols[c] == cols[c-1]) {
                        mirrInd = c-1;
                    }
                } else if (mirrInd - (c-(mirrInd+1)) >= 0 && cols[c] != cols[mirrInd - (c-(mirrInd+1))]) {
                    mirrInd = -1;
                }
            }

            if (mirrInd != -1) {
                summary += mirrInd + 1;
                cout << "col mirrInd: " << mirrInd << endl;

                grid.clear();
                continue;
            }
            
            // for (auto row : rows) {
            //     cout << row << endl;
            // }

            // for (auto col : cols) {
            //     cout << col << endl;
            // }

            grid.clear();
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