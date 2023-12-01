//
// Created by Álvaro Borrás on 28/11/23.
//

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream input_file("../input/input_day_01_part1.txt");
  std::string line;

  const std::string digits = "0123456789";
  int answer = 0;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      auto firstDigitPos = line.find_first_of(digits);
      auto lastDigitPos = line.find_last_of(digits);
      if (firstDigitPos != std::string::npos && lastDigitPos != std::string::npos)
        answer += 10 * (int)(line[firstDigitPos] - '0') + (int)(line[lastDigitPos] - '0');
    }
    input_file.close();
    std::cout << answer << std::endl;
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}