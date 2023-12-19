#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <vector>
#include <unordered_set>
#include "time_utils.h"

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_14_part1.txt");

  std::vector<std::string> grid;
  if (input_file.is_open()) {
    std::string line;
    while (std::getline(input_file, line)) { grid.push_back(line); }
    input_file.close();

    // tilt north
    for (size_t i = 0; i < grid.size(); ++i) {
      for (size_t j = 0; j < grid[i].length(); ++j) {
        if (grid[i][j] == 'O') {
          grid[i][j] = '.';
          for (int r = i; r >= 0; --r) {
            if (r == 0 || grid[r - 1][j] == '#' || grid[r - 1][j] == 'O') {
              grid[r][j] = 'O';
              break;
            }
          }
        }
      }
    }

    uint32_t ans = 0;

    for (size_t i = 0; i < grid.size(); ++i) {
      for (size_t j = 0; j < grid[i].length(); ++j) {
        if (grid[i][j] == 'O') { ans += grid.size() - i; }
      }
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