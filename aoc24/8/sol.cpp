#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? abs(a) : gcd(b, a % b);
}

int find_antinodes(const vector<pair<int, int>>& locs, vector<vector<bool>>& seen) {
    int total = 0;
    for (int i = 0; i < locs.size(); ++i) {
        int ox = locs[i].first, oy = locs[i].second;
        for (int j = i + 1; j < locs.size(); ++j) {
            int nx = locs[j].first, ny = locs[j].second;

            int dx = nx - ox, dy = ny - oy;

            pair<int, int> antinode1 = {ox - dx, oy - dy}; 
            pair<int, int> antinode2 = {nx + dx, ny + dy}; 

            if (antinode1.first >= 0 && antinode1.first < seen.size() &&
                antinode1.second >= 0 && antinode1.second < seen[0].size() &&
                !seen[antinode1.first][antinode1.second]) {
                
                seen[antinode1.first][antinode1.second] = true;
                ++total;
            }

            if (antinode2.first >= 0 && antinode2.first < seen.size() &&
                antinode2.second >= 0 && antinode2.second < seen[0].size() &&
                !seen[antinode2.first][antinode2.second]) {
                
                seen[antinode2.first][antinode2.second] = true;
                ++total;
            }
        }
    }

    return total;
}

int find_antinodes2(const vector<pair<int, int>>& locs, vector<vector<bool>>& seen) {
    int total = 0;
    int rows = seen.size();
    int cols = seen[0].size();
    set<pair<int, int>> unique_antinode_positions;

    for (int i = 0; i < locs.size(); ++i) {
        int ox = locs[i].first, oy = locs[i].second;
        for (int j = i + 1; j < locs.size(); ++j) {
            int nx = locs[j].first, ny = locs[j].second;

            int dx = nx - ox;
            int dy = ny - oy;

            int g = gcd(dx, dy);
            dx /= g;
            dy /= g;

            int x = ox, y = oy;
            while (x >= 0 && x < rows && y >= 0 && y < cols) {
                unique_antinode_positions.emplace(x, y);
                x += dx;
                y += dy;
            }

            x = nx, y = ny;
            while (x >= 0 && x < rows && y >= 0 && y < cols) {
                unique_antinode_positions.emplace(x, y);
                x -= dx;
                y -= dy;
            }

            unique_antinode_positions.emplace(ox, oy);
            unique_antinode_positions.emplace(nx, ny);
        }
    }

    for (const auto& pos : unique_antinode_positions) {
        if (!seen[pos.first][pos.second]) {
            seen[pos.first][pos.second] = true;
            ++total;
        }
    }

    return total;
}

int part1(vector<string> lines) { 
    unordered_map<char, vector<pair<int, int>>> loc_map;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            if (lines[i][j] != '.') loc_map[lines[i][j]].emplace_back(make_pair(i, j));
        }
    }

    int res = 0;
    vector<vector<bool>> seen(lines.size(), vector<bool>(lines[0].size()));
    for (const auto& [k, v] : loc_map) {
        res += find_antinodes(v, seen);
    }

    return res;
 }

int part2(vector<string> lines) { 
    unordered_map<char, vector<pair<int, int>>> loc_map;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            if (lines[i][j] != '.') loc_map[lines[i][j]].emplace_back(make_pair(i, j));
        }
    }

    int res = 0;
    vector<vector<bool>> seen(lines.size(), vector<bool>(lines[0].size()));
    for (const auto& [k, v] : loc_map) {
        res += find_antinodes2(v, seen);
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