//
// Created by Álvaro Borrás on 04/12/23.
//

#include <fstream>
#include <iostream>
#include <string>

inline bool special(char c) { return c != '.' && !('0' <= c && c <= '9'); }

const std::vector<int> dx = {0, 0, 1, 1, 1, -1, -1, -1};
const std::vector<int> dy = {1, -1, 1, 0, -1, 1, 0, -1};

int main() {
  std::ifstream input_file("../input/input_day_03_part1.txt");
  std::string line;

  long long answer = 0;
  if (input_file.is_open()) {
    std::vector<std::string> v;
    while (std::getline(input_file, line)) { v.push_back(line); }
    input_file.close();

    int nLines = (int)v.size();
    int nCols = (int)v[0].size();
    bool specialNumber = false;

    for (int i = 0; i < nLines; ++i) {
      long long curNumber = 0;
      for (int j = 0; j < nCols; ++j) {
        if ('0' <= v[i][j] && v[i][j] <= '9') {
          curNumber = 10 * curNumber + (int)(v[i][j] - '0');

          for (int neigh = 0; neigh < 8; ++neigh) {
            int n_x = i + dx[neigh];
            int n_y = j + dy[neigh];

            if (n_x < 0 || n_x >= nLines) continue;
            if (n_y < 0 || n_y >= nCols) continue;

            if (special(v[n_x][n_y])) { specialNumber = true; }
          }
        }

        if (j == nCols - 1 || !isdigit(v[i][j])) {
          if (specialNumber) {
            std::cout << "special number found " << curNumber << std::endl;
            answer += curNumber;
          }
          curNumber = 0;
          specialNumber = false;
        }
      }
    }

    std::cout << answer << std::endl;
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}