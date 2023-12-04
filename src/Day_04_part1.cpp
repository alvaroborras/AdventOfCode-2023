//
// Created by Álvaro Borrás on 04/12/23.
//

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream input_file("../input/input_day_04_part1.txt");
  std::string line;

  if (input_file.is_open()) {
    long long answer = 0;

    while (std::getline(input_file, line)) {
      std::map<int, bool> winner;
      line = line.substr(line.find(":") + 2);
      auto pos = std::find(line.begin(), line.end(), '|');
      std::string first_half(line.begin(), pos);
      std::string second_half(pos + 1, line.end());

      std::stringstream ss1(first_half);
      std::stringstream ss2(second_half);

      int i, count = 0;
      while (ss1 >> i) { winner[i] = true; }
      while (ss2 >> i) { count += winner[i]; }
      answer += count > 0 ? (1LL << (count - 1)) : 0;
    }
    input_file.close();
    std::cout << answer << std::endl;
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}