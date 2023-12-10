//
// Created by Álvaro Borrás on 10/12/23.
//

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int64_t extrapolate(const std::vector<int64_t>& v) {

  int n = (int)v.size();
  std::vector<int64_t> diff(n - 1);
  for (int i = 1; i < n; ++i) { diff[i - 1] = v[i] - v[i - 1]; }

  return (n == 1 || std::all_of(diff.begin(), diff.end(), [](int i) { return i == 0; })) ? v.back()
                                                                                         : v.back() + extrapolate(diff);
}

int main() {
  std::ifstream input_file("../input/input_day_09_part1.txt");
  // std::ifstream input_file("input.txt");

  if (input_file.is_open()) {
    std::string line;
    int64_t i, answer = 0;
    while (std::getline(input_file, line)) {
      std::stringstream ss(line);
      std::vector<int64_t> v;
      while (ss >> i) { v.push_back(i); }

      answer += extrapolate(v);
    }
    std::cout << answer << std::endl;
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}