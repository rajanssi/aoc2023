#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct triplet {
  long src;
  long dst;
  long rng;
};

using mapping_list = std::vector<triplet>;

void read_ranges(std::ifstream &file, std::string &line,
                 mapping_list &mapping) {
  while (line != "") {
    std::getline(file, line);
    long d, s, r;
    std::istringstream iss(line);
    iss >> d >> s >> r;
    mapping.push_back({s, d, r});
  }

  std::getline(file, line);
}

std::vector<long> map_seeds(std::vector<long> &seeds, mapping_list &mapping) {
  std::vector<long> remapped_seeds;
  for (long seed : seeds) {
    bool flag = false;
    for (auto map : mapping) {
      if ((map.src <= seed) && (seed <= (map.src + map.rng))) {
        flag = true;
        seed = (map.dst - map.src) + seed;
        remapped_seeds.push_back(seed);
        break;
      }
    }
    if (!flag) {
      remapped_seeds.push_back(seed);
    }
  }

  return remapped_seeds;
}

int main() {
  std::ifstream file("input");
  std::vector<long> seeds;
  mapping_list soilmap;
  mapping_list fertmap;
  mapping_list watermap;
  mapping_list lightmap;
  mapping_list tempmap;
  mapping_list hummap;
  mapping_list location;

  std::string line;
  std::getline(file, line);
  line = line.substr(line.find(":") + 2);
  std::istringstream iss(line);
  long num;

  while (iss >> num) {
    seeds.push_back(num);
  }

  for (int i = 0; i < 2; i++)
    std::getline(file, line);

  read_ranges(file, line, soilmap);
  read_ranges(file, line, fertmap);
  read_ranges(file, line, watermap);
  read_ranges(file, line, lightmap);
  read_ranges(file, line, tempmap);
  read_ranges(file, line, hummap);
  read_ranges(file, line, location);

  seeds = map_seeds(seeds, soilmap);
  seeds = map_seeds(seeds, fertmap);
  seeds = map_seeds(seeds, watermap);
  seeds = map_seeds(seeds, lightmap);
  seeds = map_seeds(seeds, tempmap);
  seeds = map_seeds(seeds, hummap);
  seeds = map_seeds(seeds, location);

  long min = std::numeric_limits<long>::max();
  for (long s : seeds)
    min = std::min(min, s);
  std::cout << min << '\n';

  return 0;
}
