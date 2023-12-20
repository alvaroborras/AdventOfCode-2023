#include <fstream>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <chrono>
#include "time_utils.h"

const int EAST = 1, NORTH = 2, SOUTH = 4, WEST = 8;

struct Beam {
  public:
  int x;
  int y;
  int direction;
  Beam(int _x, int _y, int _d) : x(_x), y(_y), direction(_d) {}
};

int main() {

  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_16_part1.txt");

  if (input_file.is_open()) {
    std::string line;
    std::vector<std::string> grid;
    while (std::getline(input_file, line)) { grid.emplace_back(line); }
    input_file.close();

    const int N = grid.size(), M = grid[0].size();

    std::vector<std::array<int, 3>> starting_points;
    for (int i = 0; i < N; ++i) {
      starting_points.push_back({i, 0, EAST});
      starting_points.push_back({i, M - 1, WEST});
    }
    for (int j = 0; j < M; ++j) {
      starting_points.push_back({0, j, SOUTH});
      starting_points.push_back({N - 1, j, NORTH});
    }

    int64_t answer = 0;

    for (auto& [i, j, dir] : starting_points) {
      std::vector<Beam> beams = {Beam(i, j, dir)};
      std::vector<std::vector<int>> energized(N, std::vector<int>(N, 0));

      bool finished = false;
      while (!finished) {
        finished = true;
        for (size_t i = 0; i < beams.size(); ++i) {
          Beam current_beam = beams[i], new_beam = current_beam;
          // if position is not valid, ignore it.
          if ((current_beam.x < 0 || current_beam.x >= N || current_beam.y < 0 || current_beam.y >= M)) { continue; }

          // if a beam with this same direction has already been processed in the cell, ignore it.
          if (energized[current_beam.x][current_beam.y] & current_beam.direction) { continue; }
          char current_point = grid[current_beam.x][current_beam.y];

          finished = false;
          energized[current_beam.x][current_beam.y] |= current_beam.direction;

          if (current_point == '/') {
            if (current_beam.direction == EAST) {
              new_beam.direction = NORTH;
              new_beam.x--;
            } else if (current_beam.direction == NORTH) {
              new_beam.direction = EAST;
              new_beam.y++;
            } else if (current_beam.direction == SOUTH) {
              new_beam.direction = WEST;
              new_beam.y--;
            } else if (current_beam.direction == WEST) {
              new_beam.direction = SOUTH;
              new_beam.x++;
            }
          } else if (current_point == '\\') {
            if (current_beam.direction == EAST) {
              new_beam.direction = SOUTH;
              new_beam.x++;
            } else if (current_beam.direction == NORTH) {
              new_beam.direction = WEST;
              new_beam.y--;
            } else if (current_beam.direction == SOUTH) {
              new_beam.direction = EAST;
              new_beam.y++;
            } else if (current_beam.direction == WEST) {
              new_beam.direction = NORTH;
              new_beam.x--;
            }
          } else if (current_point == '|' && (current_beam.direction == EAST || current_beam.direction == WEST)) {
            // change current direction and add another one in opposite direction
            beams.emplace_back(Beam(current_beam.x + 1, current_beam.y, SOUTH));
            new_beam.x--;
            new_beam.direction = NORTH;
          } else if (current_point == '-' && (current_beam.direction == NORTH || current_beam.direction == SOUTH)) {
            beams.emplace_back(Beam(current_beam.x, current_beam.y + 1, EAST));
            new_beam.y--;
            new_beam.direction = WEST;
          } else { // nothing happens
            if (current_beam.direction == EAST) { new_beam.y++; }
            if (current_beam.direction == WEST) { new_beam.y--; }
            if (current_beam.direction == NORTH) { new_beam.x--; }
            if (current_beam.direction == SOUTH) { new_beam.x++; }
          }
          beams[i] = new_beam;
        }
      }

      int64_t result = 0;
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
          if (energized[i][j]) { result++; }
        }
      }
      answer = std::max(answer, result);
    }

    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";
  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}