#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

enum class tile {
  VPIPE = 0,
  HPIPE = 1,
  NEBND = 2,
  NWBND = 3,
  SWBND = 4,
  SEBND = 5,
  GROUN = 6,
  START = 7,
  SEEN = 8,
};

constexpr tile get_tile(const char c) {
  switch (c) {
  case '|':
    return tile::VPIPE;
  case '-':
    return tile::HPIPE;
  case 'L':
    return tile::NEBND;
  case 'J':
    return tile::NWBND;
  case '7':
    return tile::SWBND;
  case 'F':
    return tile::SEBND;
  case '.':
    return tile::GROUN;
  case 'S':
    return tile::START;
  }
  return tile::SEEN;
}

constexpr bool connect_N(const tile t1, const tile t2) {
  return (t1 == tile::VPIPE || t1 == tile::NWBND || t1 == tile::NEBND) &&
         (t2 == tile::VPIPE || t2 == tile::SWBND || t2 == tile::SEBND);
}

constexpr bool connect_S(const tile t1, const tile t2) {
  return (t1 == tile::VPIPE || t1 == tile::SWBND || t1 == tile::SEBND) &&
         (t2 == tile::VPIPE || t2 == tile::NWBND || t2 == tile::NEBND);
}

constexpr bool connect_W(const tile t1, const tile t2) {
  return (t1 == tile::HPIPE || t1 == tile::SWBND || t1 == tile::NWBND) &&
         (t2 == tile::HPIPE || t2 == tile::SEBND || t2 == tile::NEBND);
}

constexpr bool connect_E(const tile t1, const tile t2) {
  return (t1 == tile::HPIPE || t1 == tile::SEBND || t1 == tile::NEBND) &&
         (t2 == tile::HPIPE || t2 == tile::SWBND || t2 == tile::NWBND);
}

void neighbor(std::vector<std::vector<tile>> &chart, std::pair<int, int> &p) {
  int row = p.first;
  int col = p.second;

  auto &t0 = chart[row][col];
  auto t1 = chart[row - 1][col];
  auto t2 = chart[row][col - 1];
  auto t3 = chart[row][col + 1];
  auto t4 = chart[row + 1][col];

  if (connect_N(t0, t1))
    p = {row - 1, col};
  else if (connect_S(t0, t4))
    p = {row + 1, col};
  else if (connect_W(t0, t2))
    p = {row, col - 1};
  else if (connect_E(t0, t3))
    p = {row, col + 1};
  else
    p = {0xDEADBEEF, 0xDEADBEEF};

  t0 = tile::SEEN;
}

void set_start(std::vector<std::vector<tile>> &chart,
               const std::pair<int, int> s, std::pair<int, int> &p1,
               std::pair<int, int> &p2) {
  int row = s.first;
  int col = s.second;

  auto t1 = chart[row - 1][col];
  auto t2 = chart[row][col - 1];
  auto t3 = chart[row][col + 1];
  auto t4 = chart[row + 1][col];

  bool first = true;
  if (connect_N(tile::VPIPE, t1)) {
    p1 = {row - 1, col};
    first = false;
  }
  if (connect_S(tile::VPIPE, t4)) {
    if (first) {
      p1 = {row + 1, col};
      first = false;
    } else
      p2 = {row + 1, col};
  }
  if (connect_W(tile::HPIPE, t2)) {
    if (first)
      p1 = {row, col - 1};
    else
      p2 = {row, col - 1};
  }
  if (connect_E(tile::HPIPE, t3)) {
    p2 = {row, col + 1};
  }
}

int traverse(std::vector<std::vector<tile>> &chart,
             const std::pair<int, int> s) {
  std::pair<int, int> p1{0xDEADBEEF, 0xDEADBEEF}, p2{0xDEADBEEF, 0xDEADBEEF};
  set_start(chart, s, p1, p2);

  std::set<std::pair<int, int>> seen;

  for (int i = 2;; i++) {
    neighbor(chart, p1);
    neighbor(chart, p2);
    if (seen.find(p1) != seen.end())
      return i;

    seen.insert(p1);
    if (seen.find(p2) != seen.end())
      return i;

    seen.insert(p2);
  }

  return 0;
}

int main() {
  std::fstream file("input");
  std::string line;

  std::vector<std::vector<tile>> tile_map;
  std::pair<int, int> start;
  std::vector<tile> padding;
  while (std::getline(file, line)) {
    if (padding.empty()) {
      for (int i = 0; i < line.length() + 2; i++) {
        padding.push_back(tile::GROUN);
      }
      tile_map.push_back(padding);
    }
    static int i = 1;
    int j = 1;
    std::vector<tile> row;
    row.push_back(tile::GROUN);
    std::istringstream iss(line);
    char c;
    while (iss >> c) {
      row.push_back(get_tile(c));
      if (c == 'S')
        start = {i, j};
      j++;
    }
    row.push_back(tile::GROUN);
    tile_map.push_back(row);
    i++;
  }
  tile_map.push_back(padding);

  std::cout << traverse(tile_map, start) << '\n';

  return 0;
}
