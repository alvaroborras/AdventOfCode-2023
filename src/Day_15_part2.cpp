#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <ranges>
#include <vector>
#include <unordered_set>
#include "time_utils.h"

const uint16_t MOD = 256;

// computes the has for a given label
inline uint16_t hash(const std::string& s) {
  uint16_t res = 0;
  for (char c : s) { res = ((res + c) * 17) % MOD; }
  return res;
}

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_15_part1.txt");

  if (input_file.is_open()) {
    std::string line;
    std::getline(input_file, line);
    input_file.close();

    std::vector<std::vector<std::string>> lens(MOD);
    std::map<std::string, uint16_t> focal_length;

    uint16_t id;
    auto remove_box = [&](const std::string& box_name) -> void {
      lens[id].erase(std::remove(lens[id].begin(), lens[id].end(), box_name), lens[id].end());
    };

    auto add_box = [&](const std::string& box_name) {
      for (std::string& s : lens[id]) {
        // if box is present, ignore query
        if (box_name == s) { return; }
      }
      lens[id].push_back(box_name);
    };

    //   just iterate over the boxes and compute the desired quantity
    auto focusing_power = [&]() -> uint64_t {
      uint64_t res = 0;
      for (uint16_t i = 0; i < MOD; ++i) {
        for (uint16_t j = 0; j < lens[i].size(); ++j) { res += (uint64_t)(1 + i) * (j + 1) * focal_length[lens[i][j]]; }
      }
      return res;
    };

    // split all the instructions by commas
    auto split_s = line | std::ranges::views::split(',');

    for (auto&& subrange : split_s) {
      std::string token(subrange.begin(), subrange.end());

      // if after processing the string, the value is -1
      // we know that we have to remove it
      int value = -1;
      std::string label = "";
      for (size_t i = 0; i < token.length(); ++i) {
        if (token[i] == '-') {
          break;
        } else if (token[i] == '=') {
          value = token[i + 1] - '0';
          break;
        } else {
          label += token[i];
        }
      }
      id = hash(label);

      // if we have to remove it, take it if possible
      if (value == -1) {
        remove_box(label);
      } else {
        add_box(label);
        focal_length[label] = value;
      }
    }

    std::cout << focusing_power() << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}