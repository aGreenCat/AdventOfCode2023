#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string DIGITS[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

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

            for (int d = 0; d < 9; d++) {
                string digit = DIGITS[d];

                if (s.size()-i >= digit.size()) {
                    if (s.substr(i, digit.size()) == digit) {
                        num = 10*(d+1);
                        break;
                    }
                }
            }

            if (num != 0) break;
        }

        for (int i = s.size()-1; i >= 0; i--) {
            if (isdigit(s[i])) {
                num += (s[i] - '0');
                break;
            }

            for (int d = 0; d < 9; d++) {
                string digit = DIGITS[d];
                
                if (s.size()-i >= digit.size()) {
                    if (s.substr(i, digit.size()) == digit) {
                        num += d+1;
                        break;
                    }
                }
            }

            if (num % 10 != 0) break;
        }

        sum += num;
        cout << sum << "  +" << num << endl;
    }

    cout << sum;

    return 0;
}