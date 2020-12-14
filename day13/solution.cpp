#include "../lib/aoc.h"
#include <numeric>
#include <regex>

int main(int argc, char *argv[]) {
    long int ans1 = 0, ans2 = 0;

    std::fstream myfile("input", std::ios_base::in);
    std::string line1, line2;
    std::getline(myfile, line1);
    std::getline(myfile, line2);
    myfile.close();

    // Time we can leave
    int mytime = std::stoi(line1);

    std::vector<std::pair<int, int>> bus_ids;
    std::pair<int, int> best_bus = {-1, 100000};
    int i = 0;

    const std::regex reg("([0-9x]+)+");
    std::sregex_token_iterator it = {line2.begin(), line2.end(), reg, 1};
    while (it != std::sregex_token_iterator()) {
        if (*it != 'x') {
            int val = std::stoi(*it);

            if (val > 0) {
                int n = mytime / val;
                int rem = mytime % val;

                // If the value is less than the time, then we must do val-rem
                // to find out how long after the bus leaves
                if (n * val < mytime)
                    rem = val - rem;

                if (rem < best_bus.second) {
                    best_bus.first = val;
                    best_bus.second = rem;
                }
            }
            bus_ids.push_back({val, i});
        }

        i++;
        it = std::next(it);
    }

    // Sort so we start with the largest ID, which means start with largest
    // increment and thus iterate to solution faster
    std::sort(bus_ids.begin(), bus_ids.end());
    std::reverse(bus_ids.begin(), bus_ids.end());

    // Pick a starting value which we know works
    long int t = bus_ids[0].first - bus_ids[0].second;
    long int step = bus_ids[0].first;

    // Loop through searching for a solution to each ID, once find a solution
    // we set the step to lowest common multiple of the current step and the id
    // which means every future increment will also be a solution for this id
    // and all previously solved ids.
    for (auto v : bus_ids) {
        while ((t + v.second) % v.first != 0)
            t += step;

        step = std::lcm(step, v.first);
    }

    ans1 = best_bus.first * best_bus.second;
    ans2 = t;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
