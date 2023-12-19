//
// Created by Álvaro Borrás on 10/12/23.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

inline int64_t gcd(const int64_t a, const int64_t b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

inline int64_t lcm(const int64_t x, const int64_t y) { return (x * y) / gcd(x, y); }

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_08_part1.txt");

  if (input_file.is_open()) {
    std::string instructions, line;
    std::getline(input_file, instructions);

    std::map<std::string, std::pair<std::string, std::string>> adj;
    std::vector<std::string> current_nodes;

    while (std::getline(input_file, line)) {
      if (line.empty()) continue;
      adj[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
      if (line[2] == 'A') { current_nodes.push_back(line.substr(0, 3)); }
    }
    input_file.close();

    int64_t ans = 1;
    for (auto& s : current_nodes) {
      int64_t period = 0;
      for (size_t i = 0; i < instructions.length() && s[2] != 'Z'; i = (i + 1) % instructions.length(), period++) {
        s = instructions[i] == 'L' ? adj[s].first : adj[s].second;
      }
      ans = lcm(ans, period);
    }

    std::cout << ans << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}