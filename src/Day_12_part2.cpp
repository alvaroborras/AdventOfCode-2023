//
// Created by Álvaro Borrás on 10/12/23.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

std::vector<bool> group_ids(int n_springs, std::vector<int>& groups) {
  std::vector<bool> is_group_end(n_springs + 1);
  is_group_end[0] = true;

  int group_end = 0;
  for (int group : groups) {
    group_end += group;
    is_group_end[group_end] = true;
  }

  return is_group_end;
}

int64_t arrangements(std::string condition, std::vector<int>& groups) {

  // compute total number of hashes
  int n_springs = std::accumulate(groups.begin(), groups.end(), 0);

  // auxiliary vector to know where the groups are delimited
  std::vector<bool> is_group_end = group_ids(n_springs, groups);

  int n = condition.size();

  // dp[i][j][k]
  //     i = index location in the string
  //     j = number of springs already put
  //     k = type character to put: 0 = '.', 1 = '#'
  auto dp = new int64_t[n + 1][17 * 5 + 1][2];

  dp[0][0][0] = 1;

  for (int i = 1; i <= n; i++) {
    if (condition[i - 1] == '#' || condition[i - 1] == '?') {
      // Possibilities for '#'
      for (int placed_springs = 1; placed_springs <= std::min(i, n_springs); placed_springs++) {
        if (is_group_end[placed_springs - 1]) {
          // at the start of a group we must have a '.'
          dp[i][placed_springs][1] = dp[i - 1][placed_springs - 1][0];
        } else {
          // if group still not complete, we must have a '#'
          dp[i][placed_springs][1] = dp[i - 1][placed_springs - 1][1];
        }
      }
    }

    if (condition[i - 1] == '.' || condition[i - 1] == '?') {
      // Possibilities for '.'
      for (int placed_springs = 0; placed_springs <= std::min(i - 1, n_springs); placed_springs++) {
        if (is_group_end[placed_springs]) {
          // in a completed group -  we can have anything
          dp[i][placed_springs][0] = dp[i - 1][placed_springs][0] + dp[i - 1][placed_springs][1];
        }
      }
    }
  }

  return dp[n][n_springs][0] + dp[n][n_springs][1];
}

int main() {
  std::ifstream input_file("../input/input_day_12_part1.txt");

  if (input_file.is_open()) {
    std::string line;

    int64_t answer = 0;
    while (std::getline(input_file, line)) {
      auto p = line.find(' ');
      std::string condition = line.substr(0, p);
      std::stringstream ss(line.substr(p));

      int i;
      std::vector<int> counts;
      while (ss >> i) {
        counts.push_back(i);
        if (ss.peek() == ',') ss.ignore();
      }
      int nCounts = (int)counts.size();

      // repeat the condition and the counts 4 times more
      for (int rep = 0; rep < 4; ++rep) {
        condition += '?' + line.substr(0, p);
        for (int i = 0; i < nCounts; ++i) { counts.push_back(counts[i]); }
      }
      answer += arrangements(condition, counts);
    }

    std::cout << answer << std::endl;

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}