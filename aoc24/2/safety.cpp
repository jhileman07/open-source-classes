#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

bool isSafe(const std::vector<int>& report) {
    int diff = report[1] - report[0];
    for (size_t i = 0; i < report.size() - 1; ++i) {
        int new_diff = report[i + 1] - report[i];
        if (abs(new_diff) > 3 || new_diff == 0 || (diff ^ new_diff) < 0) {
            std::cout << "Broke with new diff " << new_diff << " and diff " << diff << '\n';
            return false;
        }
        diff = new_diff;
    }
    return true;
}

bool isSafeWithDampener(const std::vector<int>& report) {
    if (isSafe(report)) return true;

    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> modifiedReport;
        for (size_t j = 0; j < report.size(); ++j) {
            if (j != i) modifiedReport.push_back(report[j]);
        }
        if (isSafe(modifiedReport)) return true;
    }
    return false;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::vector<std::vector<int>> in;
    std::string line;

    std::cout << "BEGINNING SCAN" << '\n';
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> nums;
        int num;

        while (iss >> num)
            nums.push_back(num);

        in.push_back(nums);
    }
    std::cout << "Found " << in.size() << " lines" << std::endl;

    int res = 0;
    for (const auto& report : in) {
        if (isSafeWithDampener(report)) res++;
    }
    std::cout << "Final sum: " << res << std::endl;

    return 0;
}
