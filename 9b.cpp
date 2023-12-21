#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int find_diff(const std::vector<int> &v) {
  std::vector<int> diff;

  bool recurse = false;
  for (int i = 1; i < v.size(); i++) {
    int d = v[i] - v[i - 1];
    if (d != 0)
      recurse = true;
    diff.push_back(d);
  }
  if (recurse)
    return v.front() - find_diff(diff);

  return v.front();
}

int main() {
  std::fstream file("input");
  std::string line;

  int total = 0;
  while (std::getline(file, line)) {
    std::vector<int> row;
    std::istringstream iss(line);
    int num;
    while (iss >> num) {
      row.push_back(num);
    }
    total += find_diff(row);
  }
  std::cout << total << '\n';

  return 0;
}
