#include "../lib/aoc.h"

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while (std::getline(myfile, line)) {
        // 1-3 a: abcde
        int dash = line.find("-");
        int space = line.find(" ") + 1;
        int colon = line.find(":") + 2;

        std::string token1 = line.substr(0, dash);
        std::string token2 = line.substr(dash + 1, space - dash);
        std::string token3 = line.substr(space, 1);
        std::string token4 = line.substr(colon, line.size() - colon);

        int r1 = std::stoi(token1);
        int r2 = std::stoi(token2);
        char target = token3[0];

        int tot = 0;
        for (unsigned long int i = 0; i < token4.size(); i++)
            if (token4[i] == target)
                tot++;

        if ((tot >= r1) && (tot <= r2))
            ans1++;

        if (((token4[r1 - 1] == target) + (token4[r2 - 1] == target)) == 1)
            ans2++;
    }
    myfile.close();

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
