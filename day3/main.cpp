#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

long long solve_line(const std::string &line) {
  std::vector<int> first_pos(10, INT_MAX);
  std::vector<int> last_pos(10, -1);

  for (int i = 0; i < line.length(); ++i) {
    int digit = line[i] - '0';
    if (digit >= 1 && digit <= 9) {
      if (first_pos[digit] == INT_MAX) {
        first_pos[digit] = i;
      }
      last_pos[digit] = i;
    }
  }

  for (int val = 99; val >= 11; --val) {
    int d1 = val / 10;
    int d2 = val % 10;
    if (d1 == 0 || d2 == 0)
      continue;

    if (first_pos[d1] != INT_MAX && last_pos[d2] != -1 &&
        first_pos[d1] < last_pos[d2]) {
      return val;
    }
  }
  return 0;
}

void solve(const std::vector<std::string> &lines) {
  long long total_joltage = 0;
  for (const auto &line : lines) {
    total_joltage += solve_line(line);
  }
  std::cout << "Total output joltage: " << total_joltage << std::endl;
}

int main() {
  std::ifstream file("input");
  if (!file.is_open()) {
    std::cerr << "Failed to open input file" << std::endl;
    return 1;
  }
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      lines.push_back(line);
    }
  }
  file.close();
  solve(lines);
  return 0;
}