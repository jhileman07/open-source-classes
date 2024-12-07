#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <map>

int main() {
  std::ifstream inputFile("input.txt");
  std::vector<int> in;
  std::map<int, int> count;
  std::string line;

  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    int n1, n2;

    iss >> n1 >> n2;
    in.push_back(n1);
    count[n2]++;
  }

  std::sort(in.begin(), in.end());
  int dist = 0;

  for (int i = 0; i < in.size(); ++i) {
    if (count.count(in[i]))
      dist += (in[i] * count[in[i]]);
  }

  std::cout << "Final sum: " << dist << std::endl;

  return 0;
}
