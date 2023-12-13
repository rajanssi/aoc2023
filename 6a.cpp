#include <array>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

int main() {
  std::fstream file("input");
  std::array<std::pair<int, int>, 4> td;

  bool first = true;
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string sink;

    iss >> sink;
    if (first) {
      iss >> td[0].first;
      iss >> td[1].first;
      iss >> td[2].first;
      iss >> td[3].first;
    } else {
      iss >> td[0].second;
      iss >> td[1].second;
      iss >> td[2].second;
      iss >> td[3].second;
    }
    first = false;
  }

  int total = 1;
  for (auto p : td) {
    int time = p.first;
    int best = p.second;
    int counter = 0;

    for (int i = 1; i < time; i++) {
      int j = time - i;
      if (i * j > best)
        counter++;
    }
    std::cout << time << " " << best << " " << counter << '\n';
    total *= std::max(1, counter);
  }

  return 0;
}
