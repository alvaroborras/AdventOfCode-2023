#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_11_part1.txt");

  if (input_file.is_open()) {
    std::string line;
    std::vector<std::string> galaxies;
    while (std::getline(input_file, line)) { galaxies.push_back(line); }
    input_file.close();

    int nRows = galaxies.size(), nCols = galaxies[1].size();
    // store the positions of the galaxies
    std::vector<std::pair<int64_t, int64_t>> pos;
    for (int i = 0; i < nRows; ++i) {
      for (int j = 0; j < nCols; ++j) {
        if (galaxies[i][j] == '#') { pos.push_back({i, j}); }
      }
    }
    int nGalaxies = (int)pos.size();

    // keep track of the rows and columns that dont have galaxies
    std::vector<int> empty_row;
    for (int i = 0; i < nRows; ++i) {
      // check if row i contains any galaxy
      bool seen = false;
      for (int j = 0; j < nCols; ++j) { seen |= galaxies[i][j] == '#'; }
      if (!seen) { empty_row.push_back(i); }
    }

    std::vector<int> empty_col;
    for (int j = 0; j < nCols; ++j) {
      bool seen = false;
      for (int i = 0; i < nRows; ++i) { seen |= galaxies[i][j] == '#'; }
      if (!seen) { empty_col.push_back(j); }
    }

    int64_t answer = 0;
    for (int i = 0; i < nGalaxies; ++i) {
      for (int j = i + 1; j < nGalaxies; ++j) {

        int64_t dx = 0;
        int64_t dy = 0;

        for (auto x : empty_row) {
          dx += (pos[i].first < x && x < pos[j].first) || (pos[j].first < x && x < pos[i].first);
        }
        for (auto y : empty_col) {
          dy += (pos[i].second < y && y < pos[j].second) || (pos[j].second < y && y < pos[i].second);
        }
        answer += abs(pos[i].first - pos[j].first) + abs(pos[i].second - pos[j].second) + (1000000 - 1) * (dx + dy);
      }
    }
    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}