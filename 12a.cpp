#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

bool isvalid(const std::string& dots, const std::vector<int>& blocks) {
    int current = 0;
    std::vector<int> seen;

    for (char c : dots) {
        if (c == '.') {
            if (current > 0) {
                seen.push_back(current);
            }
            current = 0;
        } else if (c == '#') {
            current++;
        } else {
            assert(false);
        }
    }
    if (current > 0) {
        seen.push_back(current);
    }
    return seen == blocks;
}

int f(std::string& dots, const std::vector<int>& blocks, int i) {
    if (i == dots.length()) {
        return isvalid(dots, blocks) ? 1 : 0;
    }

    if (dots[i] == '?') {
        dots[i] = '#';
        int withHash = f(dots, blocks, i + 1);
        dots[i] = '.';
        int withDot = f(dots, blocks, i + 1);
        dots[i] = '?';
        return withHash + withDot;
    } else {
        return f(dots, blocks, i + 1);
    }
}

int main() {
    std::ifstream infile("input");
    std::string line;
    int score = 0;

    while (std::getline(infile, line)) {
        size_t space_pos = line.find(' ');
        std::string dots = line.substr(0, space_pos);
        std::string blocks_str = line.substr(space_pos + 1);

        std::vector<int> blocks;
        size_t pos = 0;
        while ((pos = blocks_str.find(',')) != std::string::npos) {
            blocks.push_back(std::stoi(blocks_str.substr(0, pos)));
            blocks_str.erase(0, pos + 1);
        }
        blocks.push_back(std::stoi(blocks_str));

        score += f(dots, blocks, 0);
    }

    std::cout << score << std::endl;
    return 0;
}
