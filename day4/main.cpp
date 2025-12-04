#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> grid;
  std::ifstream file("input");
  if (!file.is_open()) {
    std::cerr << "Failed to open input file" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      grid.push_back(line);
    }
  }
  file.close();

  if (grid.empty()) {
    std::cerr << "Grid is empty" << std::endl;
    return 1;
  }

  int rows = grid.size();
  int cols = grid[0].size();
  int accessible_count = 0;

  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      if (grid[r][c] == '@') {
        int neighbor_rolls = 0;
        for (int dr = -1; dr <= 1; ++dr) {
          for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0)
              continue;

            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
              if (grid[nr][nc] == '@') {
                neighbor_rolls++;
              }
            }
          }
        }

        if (neighbor_rolls < 4) {
          accessible_count++;
        }
      }
    }
  }

  std::cout << "Accessible rolls: " << accessible_count << std::endl;

  return 0;
}