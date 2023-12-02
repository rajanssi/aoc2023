#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <array>
#include <map>

int main() {
  std::ifstream file("input");

  std::string line;
  int id = 1;
  int count = 0;
  while (std::getline(file, line)) {
    line.push_back(';');
    auto start = line.find(":") + 2;
    line.erase(0, start);
    auto end = line.find(";");

    bool flag = false;
    while (line.length() > 0) {
      std::map<std::string, int> counts = {
          {"red", 0}, {"blue", 0}, {"green", 0}};
      auto sub = line.substr(0, end);

      std::istringstream ss(sub);
      std::string token;

      while (std::getline(ss, token, ',')) {
        std::istringstream iss(token);
        int value;
        std::string color;
        iss >> value >> color;
        counts[color] += value;
      }

      for (const auto &c : counts) {
        if (c.first == "red" && c.second > 12) {
          flag = true;
          break;
        } else if (c.first == "green" && c.second > 13) {
          flag = true;
          break;
        } else if (c.first == "blue" && c.second > 14) {
          flag = true;
          break;
        }
      }

      if (flag)
        break;

      line.erase(0, end + 2);
      end = line.find(";");
    }
    if (!flag)
      count += id;

    id++;
  }

  std::cout << count << '\n';

  file.close();
  return 0;
}
