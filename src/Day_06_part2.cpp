//
// Created by Álvaro Borrás on 06/12/23.
//

#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream input_file("../input/input_day_06_part1.txt");

  std::string line;
  const size_t num_races = 4;
  if (input_file.is_open()) {

    std::stringstream ss;
    std::vector<std::pair<int64_t, int64_t>> races(num_races);
    size_t idx = 0, i;

    std::getline(input_file, line);
    ss.str(line.substr(line.find("Time:") + 5));
    while (ss >> i) { races[idx++].first = i; }

    std::getline(input_file, line);
    ss.clear();
    ss.str(line.substr(line.find("Distance:") + 9));
    idx = 0;
    while (ss >> i) { races[idx++].second = i; }

    auto concatenatePairs = [](const std::vector<std::pair<int64_t, int64_t>>& pairs) {
      return std::accumulate(pairs.begin(), pairs.end(), std::make_pair(0ll, 0ll),
                             [](const std::pair<int64_t, int64_t>& a, const std::pair<int64_t, int64_t>& b) {
                               std::string firstStr = std::to_string(a.first) + std::to_string(b.first);
                               std::string secondStr = std::to_string(a.second) + std::to_string(b.second);

                               int64_t first = std::stoll(firstStr);
                               int64_t second = std::stoll(secondStr);

                               return std::make_pair(first, second);
                             });
    };

    auto [x, y] = concatenatePairs(races);
    int64_t answer = 0;
    for (int t = 1; t < x; ++t) { answer += ((x - t) * t) > y; }
    std::cout << answer << std::endl;

    input_file.close();
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}