#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include "time_utils.h"

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_01_part1.txt");
  std::string line;

  const std::vector<std::string> numbers = {"zero", "one", "two",   "three", "four",
                                            "five", "six", "seven", "eight", "nine"};
  int answer = 0;
  if (input_file.is_open()) {
    while (std::getline(input_file, line)) {
      size_t bestFirst = line.length(), bestLast = 0;
      size_t firstNumber = 0, lastNumber = 0;

      for (int i = 0; i < 10; ++i) {
        // find first and last position of written numbers
        size_t firstOccurrence = line.find(numbers[i]);
        size_t lastOccurrence = line.rfind(numbers[i]);

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
      answer += 10 * firstNumber + lastNumber;
    }
    input_file.close();

    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}