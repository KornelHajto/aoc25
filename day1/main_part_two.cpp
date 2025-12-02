#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

void handle_turn(int& pos, long long& count_zeroes, const string& turn) {
    if (turn.empty()) return;

    char direction = turn[0];
    int distance = 0;

    try {
        distance = stoi(turn.substr(1));
    } catch (...) {
        cerr << "Warning: invalid input line: " << turn << endl;
        return;
    }

    const int MOD = 100;

    if (direction == 'R') {
        for (int i = 0; i < distance; ++i) {
            pos = (pos + 1) % MOD;
            if (pos == 0) count_zeroes++;
        }
    }
    else if (direction == 'L') {
        for (int i = 0; i < distance; ++i) {
            pos = (pos - 1 + MOD) % MOD;
            if (pos == 0) count_zeroes++;
        }
    }
}

int main() {
    int pos = 50;
    long long count_zeroes = 0;

    ifstream file("input");
    if (!file.is_open()) {
        cerr << "Error opening file 'input'.\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        handle_turn(pos, count_zeroes, line);
    }

    cout << "Password (method 0x434C49434B): " << count_zeroes << endl;
    return 0;
}
