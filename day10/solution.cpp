#include "../lib/aoc.h"

int main(int argc, char *argv[]) {
    int ans1 = 0;
    long int ans2 = 0;
    int maxv = 0;

    // O(N)
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::vector<int> adapters = {0};
    while (std::getline(myfile, line)) {
        adapters.push_back(std::stoi(line));
        maxv = std::max(std::stoi(line), maxv);
    }
    adapters.push_back(maxv + 3);
    myfile.close();

    // O(N log N)
    std::sort(adapters.begin(), adapters.end());

    // O(N)
    int num1s = 0, num3s = 0;
    for (size_t i = 1; i < adapters.size(); i++) {
        int diff = adapters[i] - adapters[i - 1];
        if (diff == 3)
            num3s++;
        else
            num1s++;
    }
    ans1 = num1s * num3s;

    // O(N)
    long int poss = 1;
    size_t lp = 0;
    size_t rp = 0;
    std::cout << adapters.size() << std::endl;
    while (rp < adapters.size()) {
        // Lets move along
        lp = rp;

        // How big a group until only one possible step?
        rp++;
        while ((rp < adapters.size()) && (adapters[rp] != adapters[rp - 1] + 3))
            rp++;

        // These are the possible subgroups
        if ((rp - lp) == 3)
            poss *= 2;
        else if ((rp - lp) == 4)
            poss *= 4;
        else if ((rp - lp) == 5)
            poss *= 7;
    }
    ans2 = poss;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
