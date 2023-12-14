#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream fin("input.txt");


    int sum = 0;

    string s;
    while (getline(fin, s)) {
        int num = 0;

        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                num = 10*(s[i] - '0');
                break;
            }
        }

        for (int i = s.size()-1; i >= 0; i--) {
            if (isdigit(s[i])) {
                num += (s[i] - '0');
                break;
            }
        }

        sum += num;
        cout << sum << endl;
    }

    cout << sum;

    return 0;
}