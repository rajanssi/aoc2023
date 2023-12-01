#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include <array>
#include <map>

const std::array<std::string, 18> substrings = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "1",   "2",   "3",     "4",    "5",    "6",   "7",     "8",     "9",
};

std::map<std::string, std::string> digits = {
  {"one",   "1"}, {"1", "1"},
  {"two",   "2"}, {"2", "2"},
  {"three", "3"}, {"3", "3"},
  {"four",  "4"}, {"4", "4"},
  {"five",  "5"}, {"5", "5"},
  {"six",   "6"}, {"6", "6"},
  {"seven", "7"}, {"7", "7"},
  {"eight", "8"}, {"8", "8"},
  {"nine",  "9"}, {"9", "9"},
};

int main() {
  std::ifstream file("input");

  int count = 0;
  std::string line;
  while (std::getline(file, line)) {
    std::string s1;
    std::string s2;

    int min = 1000;
    int max = -1;

    for (auto &sub : substrings) {
      auto pos = line.find(sub);
      if (pos == std::string::npos) {
        continue;
      }
      if ((int)pos < min) {
        s1 = digits[sub];
        min = pos;
      }

      pos = line.rfind(sub);
      if ((int)pos > max) {
        s2 = digits[sub];
        max = pos;
      }
    }

    count += std::stoi(s1 + s2);
  }

  std::cout << count << '\n';


  return 0;
}
