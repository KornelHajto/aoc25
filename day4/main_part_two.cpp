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
  int total_removed = 0;
  bool changed = true;

  while (changed) {
    changed = false;
    std::vector<std::pair<int, int>> to_remove;

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
            to_remove.push_back({r, c});
          }
        }
      }
    }

    if (!to_remove.empty()) {
      changed = true;
      total_removed += to_remove.size();
      for (const auto &p : to_remove) {
        grid[p.first][p.second] = '.'; // Remove the roll
      }
    }
  }

  std::cout << "Total removed rolls: " << total_removed << std::endl;

  return 0;
}
