#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "time_utils.h"

enum class Type {
  HighCard,
  OnePair,
  TwoPairs,
  ThreeOfAKind,
  FullHouse,
  FourOfAKind,
  FiveOfAKind,
};

struct Hand {
  std::string cards;
  int bid = 0;
  Type type = Type::HighCard;
};

Type GetHandType(const std::string& hand) {
  std::unordered_map<char, int> cardCounts;
  for (char card : hand) { cardCounts[card]++; }
  std::unordered_map<int, int> countCounts;
  for (const auto& [card, count] : cardCounts) { countCounts[count]++; }
  if (countCounts[5] == 1) {
    return Type::FiveOfAKind;
  } else if (countCounts[4] == 1) {
    return Type::FourOfAKind;
  } else if (countCounts[3] == 1 && countCounts[2] == 1) {
    return Type::FullHouse;
  } else if (countCounts[3] == 1) {
    return Type::ThreeOfAKind;
  } else if (countCounts[2] == 2) {
    return Type::TwoPairs;
  } else if (countCounts[2] == 1) {
    return Type::OnePair;
  } else {
    return Type::HighCard;
  }
}

bool compare_hand(const Hand& A, const Hand& B) {
  if (A.type == B.type) {
    static const std::vector<char> card_ranks = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    for (int i = 0; i < (int)A.cards.size(); ++i) {
      // Continue if cards are the same
      char leftCard = A.cards[i];
      char rightCard = B.cards[i];
      if (leftCard == rightCard) { continue; }

      return std::ranges::find(card_ranks, leftCard) < std::ranges::find(card_ranks, rightCard);
    }
  }
  return A.type < B.type;
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream input_file("../input/input_day_07_part1.txt");
  std::string cards, line;
  int bid;
  if (input_file.is_open()) {

    std::vector<Hand> hands;
    while (std::getline(input_file, line)) {
      std::stringstream ss(line);
      ss >> cards >> bid;
      Hand h;
      h.cards = cards;
      h.bid = bid;
      h.type = GetHandType(cards);
      hands.emplace_back(h);
    }
    input_file.close();
    std::sort(hands.begin(), hands.end(), compare_hand);
    int64_t answer = 0;
    for (size_t i = 0; i < hands.size(); ++i) { answer += hands[i].bid * (i + 1); }
    std::cout << answer << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << format_duration(diff) << "\n";

  } else {
    std::cout << "Unable to open file";
  }

  return 0;
}