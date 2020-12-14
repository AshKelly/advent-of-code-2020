#include "../lib/aoc.h"
#include <array>

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;

    std::array<char, 26> present;
    present.fill(0);
    int num_people = 0;
    while (std::getline(myfile, line)) {
        if (line == "") {
            // Anyone answered yes
            for (long unsigned int i = 0; i < 26; i++)
                if (present[i] > 0)
                    ans1++;

            // All answered yes
            for (long unsigned int i = 0; i < 26; i++)
                if (present[i] == num_people)
                    ans2++;

            // Reset counters
            present.fill(0);
            num_people = 0;
        } else {
            // Store reponses
            num_people++;
            for (long unsigned int i = 0; i < line.size(); i++)
                present[int(line[i]) - 97]++;
        }
    }
    myfile.close();

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
