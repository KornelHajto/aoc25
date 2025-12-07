#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long solveBlock(const vector<string> &grid, const vector<int> &cols) {
  vector<long long> numbers;
  char operation = '?';

  for (int c : cols) {
    string numStr = "";
    for (const string &row : grid) {
      if (c < row.length()) {
        char ch = row[c];
        if (isdigit(ch)) {
          numStr += ch;
        } else if (ch == '+' || ch == '*') {
          operation = ch;
        }
      }
    }
    if (!numStr.empty()) {
      numbers.push_back(stoll(numStr));
    }
  }

  if (numbers.empty())
    return 0;

  long long result = numbers[0];
  for (size_t i = 1; i < numbers.size(); ++i) {
    if (operation == '+') {
      result += numbers[i];
    } else if (operation == '*') {
      result *= numbers[i];
    }
  }
  return result;
}

int main() {
  vector<string> grid;
  string line;
  size_t maxLen = 0;

  while (getline(cin, line)) {
    grid.push_back(line);
    maxLen = max(maxLen, line.length());
  }

  if (grid.empty())
    return 0;

  long long grandTotal = 0;
  vector<int> currentBlockCols;

  for (size_t col = 0; col < maxLen; ++col) {
    bool isEmpty = true;
    for (const auto &row : grid) {
      if (col < row.length() && row[col] != ' ') {
        isEmpty = false;
        break;
      }
    }

    if (isEmpty) {
      if (!currentBlockCols.empty()) {
        grandTotal += solveBlock(grid, currentBlockCols);
        currentBlockCols.clear();
      }
    } else {
      currentBlockCols.push_back(col);
    }
  }

  if (!currentBlockCols.empty()) {
    grandTotal += solveBlock(grid, currentBlockCols);
  }

  cout << "Grand Total: " << grandTotal << endl;

  return 0;
}
