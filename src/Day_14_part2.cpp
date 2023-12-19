#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include "time_utils.h"

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  const uint16_t H = 100, maxIter = 150;
  const uint32_t target = 1000000000;

  std::string grid;

  std::unordered_map<std::string, int> seen;
  std::vector<std::string> list_grids(maxIter);

  std::ifstream input_file("../input/input_day_14_part1.txt");

  if (input_file.is_open()) {
    std::string line;
    while (std::getline(input_file, line)) { grid += line; }
    input_file.close();

    auto id = [&](uint16_t i, uint16_t j) -> uint16_t { return H * i + j; };

    for (uint16_t iter = 0; iter < maxIter; ++iter) {

      for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
          if (grid[id(r, c)] == 'O') {
            grid[id(r, c)] = '.';
            for (int r2 = r; r2 >= 0; r2--) {
              if (r2 == 0 || grid[id(r2 - 1, c)] == '#' || grid[id(r2 - 1, c)] == 'O') {
                grid[id(r2, c)] = 'O';
                break;
              }
            }
          }
        }
      }

      for (int j = 0; j < H; j++) {
        for (int i = 0; i < H; i++) {
          if (grid[id(i, j)] == 'O') {
            grid[id(i, j)] = '.';
            for (int c2 = j; c2 >= 0; c2--) {
              if (c2 == 0 || grid[id(i, c2 - 1)] == '#' || grid[id(i, c2 - 1)] == 'O') {
                grid[id(i, c2)] = 'O';
                break;
              }
            }
          }
        }
      }

      for (int i = H - 1; i >= 0; i--) {
        for (int j = 0; j < H; j++) {
          if (grid[id(i, j)] == 'O') {
            grid[id(i, j)] = '.';
            for (int r2 = i; r2 < H; r2++) {
              if (r2 == H - 1 || grid[id(r2 + 1, j)] == '#' || grid[id(r2 + 1, j)] == 'O') {
                grid[id(r2, j)] = 'O';
                break;
              }
            }
          }
        }
      }

      for (int j = H - 1; j >= 0; j--) {
        for (int i = 0; i < H; i++) {
          if (grid[id(i, j)] == 'O') {
            grid[id(i, j)] = '.';
            for (int c2 = j; c2 < H; c2++) {
              if (c2 == H - 1 || grid[id(i, c2 + 1)] == '#' || grid[id(i, c2 + 1)] == 'O') {
                grid[id(i, c2)] = 'O';
                break;
              }
            }
          }
        }
      }

      if (seen[grid]) {
        int ind = seen[grid] - 1;
        grid = list_grids[(target - 1 - iter) % (iter - ind) + ind];
        break;
      }
      seen[grid] = iter + 1;
      list_grids[iter] = grid;
    }

    uint32_t ans = 0;
    for (size_t i = 0; i < H; ++i) {
      for (size_t j = 0; j < H; ++j) {
        if (grid[id(i, j)] == 'O') { ans += H - i; }
      }
    }
    std::cout << ans << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}