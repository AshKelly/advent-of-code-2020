#include "../lib/aoc.h"

#include <cmath>

std::pair<int, int> rotate(std::pair<int, int> wp, int deg) {
    std::pair<int, int> dir;
    float theta = float(deg) * M_PI / 180.0;
    dir.first =
        int(round(wp.first * std::cos(theta) - wp.second * std::sin(theta)));
    dir.second =
        int(round(wp.first * std::sin(theta) + wp.second * std::cos(theta)));
    return dir;
}

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::list<std::pair<int, int>> dir = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    std::list<std::pair<int, int>>::iterator current_dir;
    current_dir = dir.begin();

    std::vector<std::pair<char, int>> directions;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while (std::getline(myfile, line))
        directions.push_back(
            {line[0], std::stoi(line.substr(1, line.size() - 1))});
    myfile.close();

    // Part 1
    std::pair<int, int> pos = {0, 0};
    for (auto d : directions) {
        if (d.first == 'N')
            pos.second += d.second;
        else if (d.first == 'S')
            pos.second -= d.second;
        else if (d.first == 'E')
            pos.first += d.second;
        else if (d.first == 'W')
            pos.first -= d.second;
        else if (d.first == 'F') {
            pos.first += (*current_dir).first * d.second;
            pos.second += (*current_dir).second * d.second;
        } else if (d.first == 'L') {
            int num = d.second / 90;
            for (int i = 0; i < num; i++) {
                if (current_dir == dir.begin())
                    current_dir = std::prev(dir.end());
                else
                    current_dir = std::prev(current_dir);
            }
        } else if (d.first == 'R') {
            int num = d.second / 90;
            for (int i = 0; i < num; i++) {
                current_dir = std::next(current_dir);
                if (current_dir == dir.end())
                    current_dir = dir.begin();
            }
        }
    }
    ans1 = std::abs(pos.first) + std::abs(pos.second);

    // Part 2
    pos = {0, 0};
    std::pair<int, int> wp = {10, 1};
    for (auto d : directions) {
        if (d.first == 'N')
            wp.second += d.second;
        else if (d.first == 'S')
            wp.second -= d.second;
        else if (d.first == 'E')
            wp.first += d.second;
        else if (d.first == 'W')
            wp.first -= d.second;
        else if (d.first == 'F') {
            pos.first += wp.first * d.second;
            pos.second += wp.second * d.second;
        } else if ((d.first == 'L') || (d.first == 'R')) {
            if (d.first == 'L')
                wp = rotate(wp, d.second);
            else
                wp = rotate(wp, -d.second);
        }
    }
    ans2 = std::abs(pos.first) + std::abs(pos.second);

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
