#include <fstream>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <array>
#include <chrono>
#include "time_utils.h"

class State {
  public:
  int last_dir;
  int times;
  std::pair<int, int> pos;

  State(int _last_dir, int _times, std::pair<int, int> _pos) : last_dir(_last_dir), times(_times), pos(_pos) {}

  bool operator<(const State& y) const {
    return this->pos < y.pos ||
           (this->pos == y.pos && (this->times < y.times || (this->times == y.times && this->last_dir < y.last_dir)));
  }
};

std::pair<int, int> operator+(const std::pair<int, int>& p, const std::pair<int, int>& q) {
  return {p.first + q.first, p.second + q.second};
}

int main() {

  auto start = std::chrono::high_resolution_clock::now();
  std::ifstream input_file("../input/input_day_17_part1.txt");

  if (input_file.is_open()) {
    std::string line;
    std::vector<std::string> grid;
    while (std::getline(input_file, line)) { grid.push_back(line); }
    input_file.close();

    int N = (int)grid.size(), M = grid[0].size();

    const std::vector<std::pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    std::map<State, int> distance;
    std::set<State> visited;
    std::set<std::pair<int, State>> Q;

    State st(0, 0, {0, 0});
    Q.insert({0, st});

    int answer = std::numeric_limits<int>::max();

    auto inside = [&](const std::pair<int, int>& p) -> bool {
      return 0 <= p.first && p.first < N && 0 <= p.second && p.second < M;
    };

    while (!Q.empty()) {
      auto [d, s] = *Q.begin();
      Q.erase(Q.begin());
      if (visited.find(s) != visited.end()) { continue; }
      visited.insert(s);

      if (s.pos.first == N - 1 && s.pos.second == M - 1) {
        // reached final position
        answer = std::min(answer, d);
      }

      for (int k = 0; k < 4; ++k) {
        if (k == (s.last_dir ^ 2)) { continue; }

        State nxt(k, (s.last_dir == k ? s.times + 1 : 1), s.pos + dirs[k]);
        if (!inside(nxt.pos) || nxt.times > 3) { continue; }
        Q.insert({d + (grid[nxt.pos.first][nxt.pos.second] - '0'), nxt});
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