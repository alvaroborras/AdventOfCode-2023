//
// Created by Álvaro Borrás on 10/12/23.
//

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main() {
  std::ifstream input_file("../input/input_day_08_part1.txt");
  // std::ifstream input_file("input.txt");

  if (input_file.is_open()) {
    std::string instructions, line;
    std::getline(input_file, instructions);

    std::map<std::string, std::pair<std::string, std::string>> adj;

    while (std::getline(input_file, line)) {
      if (line.empty()) continue;
      adj[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
    }

    int ans = 0;
    std::string current = "AAA";
    for (size_t i = 0; i < instructions.length() && current != "ZZZ"; i = (i + 1) % instructions.length(), ans++) {
      current = instructions[i] == 'L' ? adj[current].first : adj[current].second;
    }
    std::cout << ans << std::endl;

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}