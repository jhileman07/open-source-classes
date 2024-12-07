#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <unordered_set>

int find_middle_value(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules) {
  std::map<int, int> positions;
  for (int i = 0; i < update.size(); ++i) {
    positions[update[i]] = i; 
  }


  for (const auto& [a, b] : rules) {
    if (positions.count(a) && positions.count(b)) {
      if (positions[a] > positions[b]) {
        return 0;
      }
    }
  }

  return update[update.size() / 2];

}

int find_corrected_middle_value(const std::vector<int>& update, const std::vector<std::pair<int, int>>& rules) {
    int mid = find_middle_value(update, rules);
    if (mid > 0) return 0;
    std::unordered_map<int, std::unordered_set<int>> graph;

    for (const auto& [a,b] : rules) {
      graph[b].insert(a);
    }

    std::vector<int> sorted = update;
    std::sort(sorted.begin(), sorted.end(), [&](int a, int b){
        return graph[a].contains(b);
    });

    return sorted[sorted.size() / 2];
}

int solution(const std::vector<std::pair<int, int>>& rules, const std::vector<std::vector<int>> updates) {
  int res = 0;
  for (const auto& update : updates) {
    for (int val : update) std::cout << val << " ";
    int middle = find_corrected_middle_value(update, rules);
    std::cout << std::endl << "Middle number: " << middle << std::endl;
    res += middle;
  }
  return res;
}

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;

    while (std::getline(inputFile, line)) {
        if (line.empty()) break; 

        auto parts = split(line, '|');
        if (parts.size() == 2) {
            int a = std::stoi(parts[0]);
            int b = std::stoi(parts[1]);
            rules.emplace_back(a, b);
        }
    }

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        auto parts = split(line, ',');
        std::vector<int> update;
        for (const auto &part : parts) {
            update.push_back(std::stoi(part));
        }
        updates.push_back(update);
    }

    inputFile.close();

    std::cout << solution(rules, updates) << std::endl; 

    return 0;
}
