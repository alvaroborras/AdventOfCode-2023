#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

std::vector<std::string> flip_pattern(const std::vector<std::string> v) {
  size_t nRows = v.size(), nCols = v[0].size();
  std::vector<std::string> flipped(nCols, "");
  for (size_t i = 0; i < nCols; ++i) {
    for (size_t j = 0; j < nRows; ++j) { flipped[i] += v[nRows - 1 - j][i]; }
  }
  return flipped;
}

int count_horitzontal_symmetries(const std::vector<std::string>& v) {
  int nRows = (int)v.size();
  int res = 0;
  for (int i = 0; i + 1 < nRows; ++i) {
    // if there is a symmetry between row i and i+1, we compare until the end
    if (v[i] == v[i + 1]) {
      // only consider the case when two rows are the same
      bool is_symmetry = true;
      for (int k = 0; i - k >= 0 && i + 1 + k < nRows; ++k) {
        if (v[i - k] != v[i + 1 + k]) {
          is_symmetry = false;
          break;
        }
      }
      res += is_symmetry * (i + 1);
    }
  }
  return res;
}

int64_t compute_answer(const std::vector<std::string> pattern) {
  return 100 * count_horitzontal_symmetries(pattern) + count_horitzontal_symmetries(flip_pattern(pattern));
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_13_part1.txt");

  if (input_file.is_open()) {
    std::string line;

    std::vector<std::string> pattern;
    int64_t answer = 0;
    while (std::getline(input_file, line)) {
      if (line.empty()) {
        answer += compute_answer(pattern);
        pattern = std::vector<std::string>({});
      } else {
        pattern.push_back(line);
      }
    }
    input_file.close();

    answer += compute_answer(pattern);
    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}