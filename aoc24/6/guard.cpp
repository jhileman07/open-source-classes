#include <bits/stdc++.h>

using namespace std;


const std::vector<std::pair<int, int>> DIRS = {{0,-1}, {1, 0}, {0,1}, {-1,0}};

std::pair<int, int> get_start_pos(const std::vector<std::string>& grid) {
    std::pair<int, int> start;
    for (int y = 0; y < grid.size(); ++y) {
      for (int x = 0; x < grid[0].size(); ++x) {
          if (grid[y][x] == '^') start = std::make_pair(x, y);
      }
    }

    return start;
}

int part1(std::vector<std::string>& grid) {
  std::pair<int, int> start_pos = get_start_pos(grid);
  int res = 0;
  std::vector<std::vector<bool>> seen(grid.size(), std::vector<bool>(grid[0].size(), false));
  int x = start_pos.first, y = start_pos.second;
  int idx = 0;
  while (x >= 0 && y >= 0 && x < grid[0].size() && y < grid.size()) {
      if (!seen[y][x]) {
          res++;
          seen[y][x] = true;
      }
      auto& [dx, dy] = DIRS[idx];
      int new_x = x + dx, new_y = y + dy;
      if (new_x < 0 || new_y < 0 || new_x >= grid[0].size() || new_y >= grid.size()) return res;
      if (grid[new_y][new_x] == '#') {
        idx = (idx + 1) % 4;
      } else {
        x = new_x, y = new_y;
      }
  }

  return res;
}

int part2(std::vector<std::string>& grid) {
  int res = 0;
  std::pair<int, int> start_pos = get_start_pos(grid);
  for (int out_y = 0; out_y < grid.size(); ++out_y) {
    for (int out_x = 0; out_x < grid[0].size(); ++out_x) {
      if (out_y == start_pos.second && out_x == start_pos.first) continue;
      if (grid[out_y][out_x] == '#') continue;
      grid[out_y][out_x] = '#';
      std::vector<std::vector<char>> seen(grid.size(), std::vector<char>(grid[0].size(), 0));
      int idx = 0;
      int x = start_pos.first, y = start_pos.second;
      while (x >= 0 && y >= 0 && x < grid[0].size() && y < grid.size()) {
          if (seen[y][x] & (1 << idx)) {
              res++;
              break;
          }
          seen[y][x] |= (1 << idx);
          auto& [dx, dy] = DIRS[idx];
          int new_x = x + dx, new_y = y + dy;
          if (new_x < 0 || new_y < 0 || new_x >= grid[0].size() || new_y >= grid.size()) break;
          if (grid[new_y][new_x] == '#') {
            idx = (idx + 1) % 4;
          }  else {
            x = new_x, y = new_y;
          }
      }

      grid[out_y][out_x] = '.';
    }
  }
  return res;
}

int main() {
    ifstream file("input.txt");

    string line;
    vector<string> lines;
    string full_input;
    while (std::getline(file, line)) {
        lines.push_back(line);
        full_input += line;
    }

    auto p1_start = chrono::high_resolution_clock::now();
    auto p1 = part1(lines);
    auto p2_start = chrono::high_resolution_clock::now();
    auto p2 = part2(lines);
    auto p2_end = chrono::high_resolution_clock::now();
    cout << "part1: " << p1 << '\n';
    cout << "part2: " << p2 << '\n';

    auto p1_time =
        chrono::duration_cast<chrono::microseconds>(p2_start - p1_start);
    auto p2_time =
        chrono::duration_cast<chrono::microseconds>(p2_end - p2_start);
    cout << "part1(µs): " << p1_time.count() << '\n';
    cout << "part2(µs): " << p2_time.count() << '\n';
}
