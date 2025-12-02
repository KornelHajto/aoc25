#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

void handle_turn(int& passcode, int& num_of_zeroes, const string& turn) {
    if (turn.empty()) return;

    char direction = turn[0];
    int distance = 0;

    try {
        distance = stoi(turn.substr(1));
    } catch (const exception& e) {
        cerr << "Warning: Could not parse distance from input line: " << turn << endl;
        return;
    }

    const int MODULUS = 100;

    if (direction == 'L') {
        passcode = (passcode - (distance % MODULUS) + MODULUS) % MODULUS;
    }
    else if (direction == 'R') {
        passcode = (passcode + distance) % MODULUS;
    }

    if (passcode == 0) {
        num_of_zeroes++;
    }
}

int main() {
    int passcode = 50;
    int num_of_zeroes = 0;

    ifstream file("input");
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open the input file 'input'." << endl;
        return 1;
    }

    while (getline(file, line)) {
        handle_turn(passcode, num_of_zeroes, line);
    }

    file.close();

    cout << "The actual password (number of times the dial is 0) is: "
         << num_of_zeroes << endl;

    return 0;
}
