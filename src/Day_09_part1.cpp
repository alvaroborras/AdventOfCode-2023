#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

int64_t extrapolate(const std::vector<int64_t>& v) {

  int n = (int)v.size();
  std::vector<int64_t> diff(n - 1);
  for (int i = 1; i < n; ++i) { diff[i - 1] = v[i] - v[i - 1]; }

  return (n == 1 || std::all_of(diff.begin(), diff.end(), [](int i) { return i == 0; })) ? v.back()
                                                                                         : v.back() + extrapolate(diff);
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_09_part1.txt");

  if (input_file.is_open()) {
    std::string line;
    int64_t i, answer = 0;
    while (std::getline(input_file, line)) {
      std::stringstream ss(line);
      std::vector<int64_t> v;
      while (ss >> i) { v.push_back(i); }

      answer += extrapolate(v);
    }
    input_file.close();
    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}