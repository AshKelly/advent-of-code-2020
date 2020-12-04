#include <fstream>
#include <iostream>

#include <sstream>
#include <string>

#include <list>
#include <map>
#include <set>
#include <vector>

#include <algorithm>
#include <iterator>

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 1;

    std::vector<std::vector<char>> mymap;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while (std::getline(myfile, line)) {
        std::vector<char> row;
        for (int i = 0; i < line.size(); i++)
            row.push_back(line[i]);
        mymap.push_back(row);
    }
    myfile.close();

    /* Checking input read correctly */
    // for(auto &r : mymap){
    //    for(auto c : r)
    //        std::cout << c;
    //    std::cout << std::endl;
    //}

    /* Vector of all directions we must check */
    std::vector<std::pair<int, int>> dirs = {
        {1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1}};
    for (auto dir : dirs) {
        // Reset location and number of trees
        int trees = 0;
        std::pair<int, int> loc = {0, 0};

        // While we haven't reached the bottom
        while (loc.first < mymap.size()) {
            // Did we meet a tree?
            if (mymap[loc.first][loc.second] == '#')
                trees++;

            // Step along in the direction
            loc.first += dir.first;
            loc.second += dir.second;

            // This enforces periodic boundary conditions along the x-axis
            loc.second %= mymap[0].size();
        }

        ans2 *= trees;

        // Part 1 only cares about direction {1, 3}
        if (dir == std::pair<int, int>(1, 3))
            ans1 = trees;
    }

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
