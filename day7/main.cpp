
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ifstream infile("input");
  if (!infile) {
    cerr << "Failed to open file \"input\"\n";
    return 2;
  }

  vector<string> grid;
  string line;
  while (getline(infile, line))
    grid.push_back(line);
  infile.close();

  if (grid.empty()) {
    cout << 0 << "\n";
    return 0;
  }

  int R = (int)grid.size();
  int C = (int)grid[0].size();

  int start_row = -1, start_col = -1;
  for (int r = 0; r < R && start_row == -1; ++r) {
    for (int c = 0; c < C; ++c) {
      if (grid[r][c] == 'S') {
        start_row = r;
        start_col = c;
        break;
      }
    }
  }
  if (start_row == -1) {
    cerr << "No starting position 'S' found in input\n";
    return 2;
  }

  unordered_set<int> beams;
  beams.insert(start_col);

  long long split_count = 0;

  for (int r = start_row + 1; r < R; ++r) {
    unordered_set<int> current = beams;
    unordered_set<int> processed;  // columns already processed this row
    unordered_set<int> next_beams; // beams that survive to the next row

    while (!current.empty()) {
      unordered_set<int> newly_spawned;
      for (int c : current) {
        if (c < 0 || c >= C)
          continue;
        if (processed.count(c))
          continue;
        processed.insert(c);

        char ch = grid[r][c];
        if (ch == '^') {
          ++split_count;
          int left = c - 1;
          int right = c + 1;
          if (left >= 0)
            newly_spawned.insert(left);
          if (right < C)
            newly_spawned.insert(right);
        } else {
          next_beams.insert(c);
        }
      }
      current.swap(newly_spawned);
    }

    beams.swap(next_beams);
    if (beams.empty())
      break; // no beams left
  }

  cout << split_count << "\n";
  return 0;
}
