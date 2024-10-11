#include <fstream>
#include <iostream>
#include <string>

#include <utility>
#include <vector>

int main() {
  std::fstream file("input");
  std::string line;

  std::vector<bool> e_rows(140, true);
  std::vector<bool> e_cols(140, true);

  std::vector<std::pair<long, long>> planets;

  int r = 0;
  while (std::getline(file, line)) {
    for (int i = 0; i < line.length(); i++) {
      if (line[i] != '.') {
        e_rows[r] = false;
        e_cols[i] = false;

        planets.push_back({r, i});
      }
    }
    r++;
  }

  std::vector<long> rows(140, 0);
  std::vector<long> cols(140, 0);

  for (int i = 1; i < rows.size(); i++) {
    rows[i] = rows[i - 1] + 1;
    if (e_rows[i]) {
      rows[i] += 1'000'000;
    }
  }
  for (int i = 1; i < cols.size(); i++) {
    cols[i] = cols[i - 1] + 1;
    if (e_cols[i]) {
      cols[i] += 1'000'000;
    }
  }

  for (auto &p : planets) {
    p.first = rows[p.first];
    p.second = cols[p.second];
  }

  long paths = 0;
  for (int i = 0; i < planets.size(); i++) {
    for (int j = i + 1; j < planets.size(); j++) {
      auto p1 = planets[i];
      auto p2 = planets[j];

      long path =
          std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
      paths += path;
    }
  }

  std::cout << paths << '\n';

  return 0;
}
