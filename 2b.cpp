#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <array>
#include <map>

int main() {
  std::ifstream file("input");

  std::string line;
  int count = 0;
  while (std::getline(file, line)) {
    line.push_back(';');
    auto start = line.find(":") + 2;
    line.erase(0, start);
    auto end = line.find(";");

    bool flag = false;
    std::map<std::string, int> counts = {{"red", 0}, {"blue", 0}, {"green", 0}};
    while (line.length() > 0) {
      auto sub = line.substr(0, end);

      std::istringstream ss(sub);
      std::string token;

      while (std::getline(ss, token, ',')) {
        std::istringstream iss(token);
        int value;
        std::string color;
        iss >> value >> color;
        counts[color] = std::max(value, counts[color]);
      }

      line.erase(0, end + 2);
      end = line.find(";");
    }

    int power = 1;
    for (const auto &c : counts) {
      power *= c.second;
    }
    count += power;
  }

  std::cout << count << '\n';
  file.close();

  return 0;
}
