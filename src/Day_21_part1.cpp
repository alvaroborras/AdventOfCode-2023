#include <fstream>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <chrono>
#include "time_utils.h"

int main() {

  auto start = std::chrono::high_resolution_clock::now();
  const int MAX_STEPS = 64;

  std::ifstream input_file("../input/input_day_21_part1.txt");
  //   std::ifstream input_file("input.txt");

  if (input_file.is_open()) {
    std::string line;
    std::vector<std::string> grid;
    while (std::getline(input_file, line)) { grid.push_back(line); }
    input_file.close();

    int N = (int)grid.size(), M = grid[0].size();

    std::pair<int, int> starting_pos = {0, 0};
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        if (grid[i][j] == 'S') {
          starting_pos = {i, j};
          break;
        }
      }
    }

    const std::vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
    const int INF = 1e9;
    std::vector<std::vector<int>> dist(N, std::vector<int>(M, INF));
    auto dfs = [&](auto self, std::pair<int, int> u) -> void {
      int x = u.first, y = u.second;
      for (int d = 0; d < 4; ++d) {
        int new_x = x + dx[d], new_y = y + dy[d];
        if (new_x < 0 || new_x >= N || new_y < 0 || new_y >= M || grid[new_x][new_y] == '#') { continue; }
        if (dist[new_x][new_y] > dist[x][y] + 1 && dist[x][y] + 1 <= MAX_STEPS) {
          dist[new_x][new_y] = dist[x][y] + 1;
          self(self, {new_x, new_y});
        }
      }
    };

    dist[starting_pos.first][starting_pos.second] = 0;
    dfs(dfs, starting_pos);

    int answer = 0;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        // only count positions that are at most 64 units away
        // position is reachable in 64 steps if it is an even number of units away
        answer += dist[i][j] <= MAX_STEPS && (dist[i][j] % 2 == 0);
      }
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