#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int getValue(char card) {
  if (card == 'A')
    return 14;
  if (card == 'K')
    return 13;
  if (card == 'Q')
    return 12;
  if (card == 'J')
    return 11;
  if (card == 'T')
    return 10;
  return card - '0';
}

int getHandType(const std::string &hand) {
  std::map<char, int> counts;
  for (char card : hand) {
    counts[card]++;
  }

  if (counts.size() == 1)
    return 7;
  if (counts.size() == 2) {
    for (auto &p : counts) {
      if (p.second == 4 || p.second == 1)
        return 6;
      else
        return 5;
    }
  }
  if (counts.size() == 3) {
    for (auto &p : counts) {
      if (p.second == 3)
        return 4;
    }
    return 3;
  }
  if (counts.size() == 4)
    return 2;
  return 1;
}

bool compareHands(const std::pair<std::string, int> &a,
                  const std::pair<std::string, int> &b) {
  int typeA = getHandType(a.first);
  int typeB = getHandType(b.first);

  if (typeA != typeB)
    return typeA > typeB;

  for (size_t i = 0; i < a.first.length(); ++i) {
    int valA = getValue(a.first[i]);
    int valB = getValue(b.first[i]);
    if (valA != valB)
      return valA > valB;
  }
  return false;
}

int main() {
  std::ifstream file("input");
  std::vector<std::pair<std::string, int>> hands;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string cards;
    int bet;

    iss >> cards;
    iss >> bet;

    hands.push_back({cards, bet});
  }

  std::sort(hands.begin(), hands.end(), compareHands);

  int totalWinnings = 0;
  for (size_t i = 0; i < hands.size(); i++) {
    totalWinnings += hands[i].second * (hands.size() - i);
  }

  std::cout << "Total winnings: " << totalWinnings << std::endl;
  return 0;
}
