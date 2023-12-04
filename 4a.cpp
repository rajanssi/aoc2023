#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream file("input");
  std::vector<std::set<int>> winning_tickets;
  std::vector<std::vector<int>> player_tickets;

  std::string line;
  while (std::getline(file, line)) {
    auto start = line.find(":") + 2;
    line = line.substr(start);
    std::istringstream iss(line);
    std::set<int> wt;
    int num;
    while (iss >> num) {
      wt.insert(num);
    }
    winning_tickets.push_back(wt);

    start = line.find("|") + 2;
    line = line.substr(start);
    std::istringstream iss2(line);

    std::vector<int> pt;
    while (iss2 >> num) {
      pt.push_back(num);
    }
    player_tickets.push_back(pt);
  }
  file.close();

  int count = 0;
  for (int i = 0; i < winning_tickets.size(); i++) {
    const auto &s = winning_tickets[i];
    const auto &t = player_tickets[i];

    int c = 0;
    for (auto p : t) {
      if (s.find(p) != s.end()) {
        if (c == 0)
          c = 1;
        else
          c = c << 1;
      }
    }
    count += c;
  }

  std::cout << count << '\n';

  return 0;
}
