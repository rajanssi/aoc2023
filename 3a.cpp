#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

std::set<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::pair<int, int> scan_number(const std::string &line, const int begin) {
  std::string s;

  int i = begin;

  while (digits.find(line[i]) != digits.end()) {
    s += line[i];
    i++;
  }

  return {std::stoi(s), i - begin};
}

bool scan_symbol(const std::vector<std::string> &lines, const int row,
                 const int begin, const int end) {

  const auto &line0 = lines[row - 1];
  const auto &line1 = lines[row];
  const auto &line2 = lines[row + 1];

  if (line1[begin - 1] != '.' || line1[end] != '.') {
    return true;
  }

  for (int i = begin - 1; i < end + 1; i++) {
    if (line0[i] != '.' || line2[i] != '.')
      return true;
  }

  return false;
}

int main() {
  std::ifstream file("input");

  std::vector<std::string> lines;
  std::string line;
  int n = 0;

  while (std::getline(file, line)) {
    line.insert(0, 1, '.');
    line.push_back('.');
    lines.push_back(line);
    n = line.length();
  }

  std::string bufferline = "";
  for (int i = 0; i < n; i++) {
    bufferline += '.';
  }

  lines.insert(lines.begin(), bufferline);
  lines.push_back(bufferline);

  int count = 0;
  for (int i = 1; i < lines.size(); i++) {
    const std::string &curline = lines[i];
    for (int j = 0; j < curline.length(); j++) {
      if (digits.find(curline[j]) != digits.end()) {
        auto num = scan_number(curline, j);
        if (scan_symbol(lines, i, j, j + num.second)) {
          count += num.first;
        }
        j += num.second;
      }
    }
  }

  std::cout << count << '\n';

  return 0;
}
