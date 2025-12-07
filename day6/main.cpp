#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trim(const string &str) {
  size_t first = str.find_first_not_of(" \t\r\n");
  if (string::npos == first)
    return "";
  size_t last = str.find_last_not_of(" \t\r\n");
  return str.substr(first, (last - first + 1));
}

bool isColumnEmpty(const vector<string> &grid, int colIndex) {
  for (const auto &row : grid) {
    if (colIndex < row.length() && row[colIndex] != ' ') {
      return false;
    }
  }
  return true;
}

long long solveBlock(const vector<string> &blockRows) {
  vector<long long> numbers;
  char operation = '?';

  for (const string &row : blockRows) {
    string cleanRow = trim(row);
    if (cleanRow.empty())
      continue;

    if (cleanRow.find('+') != string::npos) {
      operation = '+';
    } else if (cleanRow.find('*') != string::npos) {
      operation = '*';
    } else {
      try {
        numbers.push_back(stoll(cleanRow));
      } catch (...) {
      }
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
    if (isColumnEmpty(grid, col)) {
      if (!currentBlockCols.empty()) {
        vector<string> blockRows;
        for (const auto &row : grid) {
          string extracted = "";
          for (int c : currentBlockCols) {
            if (c < row.length())
              extracted += row[c];
          }
          if (!trim(extracted).empty()) {
            blockRows.push_back(extracted);
          }
        }
        grandTotal += solveBlock(blockRows);
        currentBlockCols.clear();
      }
    } else {
      currentBlockCols.push_back(col);
    }
  }

  if (!currentBlockCols.empty()) {
    vector<string> blockRows;
    for (const auto &row : grid) {
      string extracted = "";
      for (int c : currentBlockCols) {
        if (c < row.length())
          extracted += row[c];
      }
      if (!trim(extracted).empty()) {
        blockRows.push_back(extracted);
      }
    }
    grandTotal += solveBlock(blockRows);
  }

  cout << "Grand Total: " << grandTotal << endl;

  return 0;
}
