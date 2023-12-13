#include <array>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

int main() {
  std::fstream file("input");
  long time = {};
  long best = {};

  std::string line;
  while (std::getline(file, line)) {
    static bool first = true;
    std::istringstream iss(line);
    std::string sink;
    std::string num;

    iss >> sink;
    while (iss >> sink) {
      num += sink;
    }
    if (first) {
      time = std::stol(num);
    } else {
      best = std::stol(num);
    }
    first = false;
  }

  long count = 0;
  for (long i = 0; i < time; i++) {
    long j = time - i;
    if (i * j > best) {
      count = j - i + 1;
      break;
    }
  }
  std::cout << count << '\n';

  return 0;
}
