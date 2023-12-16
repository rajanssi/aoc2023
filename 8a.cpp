#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

struct node {
  std::string name;
  std::pair<std::string, std::string> links;
};

int main() {
  std::ifstream file("input");
  std::map<std::string, node> node_map;

  std::string line;
  std::getline(file, line);
  std::deque<int> lr;
  for (char c : line)
    if (c == 'L')
      lr.push_back(0);
    else
      lr.push_back(1);

  while (std::getline(file, line)) {
    if (line.empty())
      continue;
    std::istringstream iss(line);
    std::string sink;
    iss >> sink;
    node n1 = node{.name = sink};
    iss >> sink;
    iss >> sink;
    node n2 = node{.name = sink.substr(1, 3)};
    iss >> sink;
    node n3 = node{.name = sink.substr(0, 3)};
    n1.links.first = n2.name;
    n1.links.second = n3.name;
    node_map[n1.name] = n1;
  }

  auto node = node_map["AAA"];
  int count = 0;
  while (node.name != "ZZZ") {
    int dir = lr.front();
    lr.pop_front();
    lr.push_back(dir);
    if (!dir)
      node = node_map[node.links.first];
    else
      node = node_map[node.links.second];
    count++;
  }

  std::cout << count << '\n';

  return 0;
}
