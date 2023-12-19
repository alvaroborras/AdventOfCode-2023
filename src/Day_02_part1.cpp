#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "time_utils.h"

std::vector<int> process_string(const std::string& str, std::map<std::string, int> color_ID) {
  std::vector<int> color_count(3);

  std::stringstream ss(str);
  std::string box;
  while (std::getline(ss, box, ';')) {
    std::stringstream ss2(box);
    std::string token;
    while (std::getline(ss2, token, ',')) {
      std::stringstream ss3(token);
      int number;
      std::string color;
      ss3 >> number >> color;
      color_count[color_ID[color]] = std::max(color_count[color_ID[color]], number);
    }
  }
  return color_count;
}

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_02_part1.txt");
  std::string line;

  // We can have at most 12 red cubes, 13 green cubes and 14 blue cubes.
  const std::vector<int> max_cubes = {12, 13, 14};
  std::map<std::string, int> color_ID;
  color_ID["red"] = 0;
  color_ID["green"] = 1;
  color_ID["blue"] = 2;

  // offset to read game id
  const size_t game_idx = 5;

  if (input_file.is_open()) {

    int answer = 0;
    while (getline(input_file, line)) {

      std::string digit_str = line.substr(game_idx, game_idx + 5);
      int game_id = std::stoi(digit_str.substr(0, digit_str.find(":")));

      std::vector<int> color_count = process_string(line.substr(line.find(":") + 2), color_ID);
      bool valid = true;
      for (int i = 0; i < 3; ++i) {
        if (color_count[i] > max_cubes[i]) {
          valid = false;
          break;
        }
      }
      if (valid) { answer += game_id; }
    }
    input_file.close();

    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";

  } else {
    std::cout << "Unable to open input_file" << std::endl;
  }

  return 0;
}