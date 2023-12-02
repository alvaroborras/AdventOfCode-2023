//
// Created by Álvaro Borrás on 02/12/23.
//

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>


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

  std::ifstream file("../input/input_day_02_part1.txt");
  std::string line;

  std::map<std::string, int> color_ID;
  color_ID["red"] = 0;
  color_ID["green"] = 1;
  color_ID["blue"] = 2;

  if (file.is_open()) {
    long long answer = 0;
    while (getline(file, line)) {
      std::vector<int> color_count = process_string(line.substr(line.find(":") + 2), color_ID);
      answer += std::accumulate(color_count.begin(), color_count.end(), 1, std::multiplies<int>());
    }
    std::cout << answer << std::endl;
    file.close();
  } else {
    std::cout << "Unable to open file" << std::endl;
  }

  return 0;
}