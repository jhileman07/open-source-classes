#include <bits/stdc++.h>

using namespace std;

int part1(vector<string> lines) { 
    string line = lines[0];
    
    vector<char> fs(-1, line.size());
    int i = 0;
    int id = 0;
    for (int j = 0; j < fs.size(); j+=2) {
        int size = line[j];
        int empty = line[j+1];

        while (size--) {
            fs[i] = id;
            i++;
        }
        i+=empty;
        id++;
        
    }

    for (char& val : fs) {
        cout << val << " ";
    }
    return 0;
 }

int part2(vector<string> lines) { 
    return 0;
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