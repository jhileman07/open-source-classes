#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::string XMAS = "XMAS";
const std::vector<std::pair<int, int>> DIRS = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

int searchWord(const std::vector<std::string>& grid, int x, int y, int dx, int dy) {
    for (int i = 0; i < XMAS.size(); ++i) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (!isValid(nx, ny, grid.size(), grid[0].size()) || grid[nx][ny] != XMAS[i]) {
            return 0;
        }
    }
    return 1; 
}

int countXMAS(const std::vector<std::string>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    int total = 0;

    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            for (const auto& dir : DIRS) {
                total += searchWord(grid, x, y, dir.first, dir.second);
            }
        }
    }

    return total;
}



bool matchesPattern(const std::vector<std::string>& grid, int x, int y, const std::vector<std::string>& pattern) {
    int rows = grid.size(), cols = grid[0].size();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int nx = x + i - 1; 
            int ny = y + j - 1;

            if (nx < 0 || ny < 0 || nx >= rows || ny >= cols) {
                return false;
            }

            if (pattern[i][j] != '.' && grid[nx][ny] != pattern[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int searchCross(const std::vector<std::string>& grid, int x, int y) {
    const std::vector<std::vector<std::string>> patterns = {
        {"M.M", ".A.", "S.S"},
        {"M.S", ".A.", "M.S"},
        {"S.S", ".A.", "M.M"},
        {"S.M", ".A.", "S.M"}
    };

    int matches = 0;
    for (const auto& pattern : patterns) {
        if (matchesPattern(grid, x, y, pattern)) {
            ++matches;
        }
    }

    return matches;
}


int countMAS(const std::vector<std::string>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    int res = 0;

    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (grid[x][y] == 'A') res += searchCross(grid, x, y);
        }
    }

    return res;
}


int main() {
    std::ifstream inputFile("input.txt");
    std::vector<std::string> grid;
    std::string line;

    while (std::getline(inputFile, line)) {
        grid.push_back(line);
    }

    std::cout << countMAS(grid) << std::endl;
    return 0;
}
