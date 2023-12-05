//
// Created by Álvaro Borrás on 05/12/23.
//

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {
  std::ifstream input_file("../input/input_day_05_part1.txt");
  std::string line;

  static size_t num_seeds;

  if (input_file.is_open()) {

    std::vector<int64_t> seeds, next_seeds;
    int64_t dest_range_start, source_range_start, range_length;

    while (std::getline(input_file, line)) {
      if (line.empty()) { continue; }
      size_t pos_seeds = line.find("seeds:");
      if (pos_seeds != std::string::npos) { // contains seed list
        std::stringstream ss_seeds(line.substr(pos_seeds + 7));
        int64_t seed;
        while (ss_seeds >> seed) { seeds.push_back(seed); }
        num_seeds = seeds.size();
        next_seeds = seeds;
        continue;
      }

      size_t pos_map = line.find("-to-"); // it contains the mapping list
      if (pos_map != std::string::npos) {
        seeds = next_seeds;
        continue;
      }

      std::stringstream ss(line);
      ss >> dest_range_start >> source_range_start >> range_length;
      for (int i = 0; i < num_seeds; ++i) {
        if (source_range_start <= seeds[i] && seeds[i] < source_range_start + range_length) {
          next_seeds[i] = seeds[i] - source_range_start + dest_range_start;
        }
      }
    }
    seeds = next_seeds;
    std::cout << *(std::min_element(seeds.begin(), seeds.end())) << std::endl;
    input_file.close();
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}