#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const vector<pair<int, int>> DIRS = {{-1,0}, {1,0}, {0,1}, {0,-1}};

int find_sum(vector<string>& grid, pair<int, int> start) {
    queue<pair<int, int>> q;
    q.push(start);
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> seen(rows, vector<bool>(cols, false));
    int res = 0;

    while (!q.empty()) {
        auto& [r, c] = q.front();
        q.pop();
        int val = grid[r][c] - '0';

        if (val == 9) {
            res++;
            continue;
        }

        for (auto& [dr, dc] : DIRS) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !seen[nr][nc] && (val + 1 == (grid[nr][nc] - '0'))) {
                seen[nr][nc] = true;
                q.push(make_pair(nr, nc));
            }
        }

    }

    return res;

}

int part1(vector<string> lines) { 
    int res = 0;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[0].size(); ++j) {
            char c = lines[i][j];
            if (c == '0') res += find_sum(lines, make_pair(i, j));
        }
    }

    return res;
 }

int find_sum2(vector<string>& grid, pair<int, int> start) {
    int rows = grid.size(), cols = grid[0].size();
    queue<vector<pair<int, int>>> q; 
    set<vector<pair<int, int>>> uniquePaths; 

    q.push({start});

    while (!q.empty()) {
        auto path = q.front();
        q.pop();

        auto [r, c] = path.back();
        int val = grid[r][c] - '0';

        if (val == 9) {
            uniquePaths.insert(path);
            continue;
        }

        for (auto& [dr, dc] : DIRS) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && (val + 1 == (grid[nr][nc] - '0'))) {
                auto newPath = path;
                newPath.emplace_back(nr, nc);
                q.push(newPath);
            }
        }
    }

    return uniquePaths.size();
}

int part2(vector<string> lines) { 
    int res = 0;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[0].size(); ++j) {
            char c = lines[i][j];
            if (c == '0') res += find_sum2(lines, make_pair(i, j));
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