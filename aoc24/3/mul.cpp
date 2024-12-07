#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <regex>

int main() {
    std::ifstream inputFile("input.txt");
    long long res = 0;
    std::string data((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();
    std::regex pattern(R"((mul\((\d+),(\d+)\))|(do\(\))|(don\'t\(\)))");
    bool enabled = true;    
    auto matches_begin = std::sregex_iterator(data.begin(), data.end(), pattern);
    auto matches_end = std::sregex_iterator();

    for (std::sregex_iterator match = matches_begin; match != matches_end; ++match) {
      std::smatch val = *match;
      if (val[4].matched) enabled = true;
      else if (val[5].matched) enabled = false;
      else if (enabled && val[2].matched && val[3].matched) {
        std::cout << "Num 1: " << val[2] << " and Num 2: " << val[3] << std::endl;
        res += std::stoi(val[2].str()) * std::stoi(val[3].str());
      }
    }
    std::cout << res << std::endl;
    return 0;
}
