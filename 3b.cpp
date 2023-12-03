#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

std::set<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::pair<int, int> scan_number(const std::string &line, const int begin,
                                std::vector<int> &num_line, int num_count) {
  std::string s;
  int i = begin;

  while (digits.find(line[i]) != digits.end()) {
    s += line[i];
    num_line[i] = num_count;
    i++;
  }

  return {std::stoi(s), i - begin};
}

int scan_symbol(const std::vector<std::vector<int>> &indices,
                const std::vector<int> &counts, const int row,
                const int begin) {

  std::set<int> seen_counts;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = begin - 1; j <= begin + 1; j++) {
      seen_counts.insert(counts[indices[i][j]]);
    }
  }

  seen_counts.erase(0);

  if (seen_counts.size() == 2) {
    int count = 1;
    for (int i : seen_counts)
      count *= i;
    return count;
  }

  return 0;
}

int main() {
  std::ifstream file("input");

  std::vector<std::string> lines;
  std::vector<std::vector<int>> indices;
  std::vector<int> counts(1);
  std::string line;
  int n = 0;

  while (std::getline(file, line)) {
    line.insert(0, 1, '.');
    line.push_back('.');
    lines.push_back(line);
    n = line.length();
  }
  file.close();

  std::string bufferline = "";
  for (int i = 0; i < n; i++) {
    bufferline += '.';
  }

  lines.insert(lines.begin(), bufferline);
  lines.push_back(bufferline);

  indices.push_back(std::vector<int>(n));
  int num_count = 1;
  for (int i = 1; i < lines.size(); i++) {
    const std::string &curline = lines[i];
    std::vector<int> num_line(n);
    for (int j = 0; j < curline.length(); j++) {
      if (digits.find(curline[j]) != digits.end()) {
        auto num = scan_number(curline, j, num_line, num_count);
        counts.push_back(num.first);
        j += num.second;
        num_count++;
      }
    }
    indices.push_back(num_line);
  }

  int count = 0;
  for (int row = 1; row < lines.size(); row++) {
    const std::string &curline = lines[row];
    for (int j = 0; j < curline.length(); j++) {
      if (curline[j] == '*') {
        count += scan_symbol(indices, counts, row, j);
      }
    }
  }

  std::cout << count << '\n';

  return 0;
}
