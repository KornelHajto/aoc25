#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

unsigned long long solve_line(const std::string &line) {
  if (line.length() < 12)
    return 0;

  std::string result = "";
  int current_idx = 0;

  for (int k = 0; k < 12; ++k) {
    int limit = line.length() - 12 + k;

    char max_digit = 0;
    int max_idx = -1;

    for (int j = current_idx; j <= limit; ++j) {
      if (line[j] > max_digit) {
        max_digit = line[j];
        max_idx = j;
      }
    }

    result += max_digit;
    current_idx = max_idx + 1;
  }

  try {
    return std::stoull(result);
  } catch (...) {
    std::cerr << "Error parsing result: " << result << std::endl;
    return 0;
  }
}

int main() {
  std::ifstream file("input");
  if (!file.is_open()) {
    std::cerr << "Failed to open input file" << std::endl;
    return 1;
  }

  std::string line;
  unsigned long long total_joltage = 0;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      total_joltage += solve_line(line);
    }
  }

  std::cout << "Total output joltage: " << total_joltage << std::endl;

  return 0;
}
