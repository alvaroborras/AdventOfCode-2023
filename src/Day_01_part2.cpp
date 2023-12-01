//
// Created by Álvaro Borrás on 28/11/23.
//

#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream input_file("../input/input_day_01_part1.txt");
  std::string line;

  const std::vector<std::string> numbers = {"zero", "one", "two",   "three", "four",
                                            "five", "six", "seven", "eight", "nine"};
  int answer = 0;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      int bestFirst = line.length(), bestLast = 0;
      int firstNumber = 0, lastNumber = 0;

      for (int i = 0; i < 10; ++i) {
        // find first and last position of written numbers
        int firstOccurrence = line.find(numbers[i]);
        int lastOccurrence = line.rfind(numbers[i]);

        // take the first position
        if (firstOccurrence != std::string::npos && firstOccurrence <= bestFirst) {
          firstNumber = i;
          bestFirst = firstOccurrence;
        }

        // take the last position
        if (lastOccurrence != std::string::npos && lastOccurrence >= bestLast) {
          lastNumber = i;
          bestLast = lastOccurrence;
        }

        // find digits
        firstOccurrence = line.find((char)(i + '0'));
        lastOccurrence = line.rfind((char)(i + '0'));

        if (firstOccurrence != std::string::npos && firstOccurrence <= bestFirst) {
          firstNumber = i;
          bestFirst = firstOccurrence;
        }

        if (lastOccurrence != std::string::npos && lastOccurrence >= bestLast) {
          lastNumber = i;
          bestLast = lastOccurrence;
        }
      }
      std::cout << firstNumber << "  " << lastNumber << std::endl;
      answer += 10 * firstNumber + lastNumber;
    }
    input_file.close();
    std::cout << answer << std::endl;
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}