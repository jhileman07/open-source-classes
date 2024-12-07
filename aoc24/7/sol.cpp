#include <bits/stdc++.h>


using namespace std;

typedef long long ll;

bool backtrack(const std::vector<ll>& vals, int i, ll total, ll cur) {
    if (cur > total || cur < 0) return false;
    if (i == vals.size()) {
        return cur == total;
    }

    return backtrack(vals, i + 1, total, cur + vals[i]) || backtrack(vals, i + 1, total, cur * vals[i]);
}

bool backtrack2(const std::vector<ll>& vals, int i, ll total, ll cur) {
    if (cur > total || cur < 0) return false;
    if (i == vals.size()) {
        return cur == total;
    }

    std::string now = to_string(cur), next = to_string(vals[i]);
    string next_str = now + next;
    ll new_val = std::stoll(next_str);

    return backtrack2(vals, i + 1, total, cur + vals[i]) || backtrack2(vals, i + 1, total, cur * vals[i]) || backtrack2(vals, i + 1, total, new_val);
}

ll part1(vector<string> lines) { 
    ll res = 0;
    for (const auto& line : lines) {
        std::istringstream iss(line);
        std::string l, r;
        std::getline(iss, l, ':');
        std::getline(iss, r);

        ll total = std::stoll(l);
        std::istringstream right(r);
        vector<ll> nums;
        ll num;
        while (right >> num) {
            nums.push_back(num);
        }

        if (backtrack(nums, 1, total, nums[0])) res += total;
    }

    return res;
}

ll part2(vector<string> lines) { 
    ll res = 0;
    for (const auto& line : lines) {
        std::istringstream iss(line);
        std::string l, r;
        std::getline(iss, l, ':');
        std::getline(iss, r);

        ll total = std::stoll(l);
        std::istringstream right(r);
        vector<ll> nums;
        ll num;
        while (right >> num) {
            nums.push_back(num);
        }

        if (backtrack2(nums, 1, total, nums[0])) res += total;
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