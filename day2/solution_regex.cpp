#include <fstream>
#include <iostream>

#include <sstream>
#include <string>

#include <regex>

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::regex pieces_regex("(\\d+)-(\\d+) ([a-z]): ([a-z]+)");

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::smatch pieces_match;
    while (std::getline(myfile, line)) {
        std::regex_search(line, pieces_match, pieces_regex);
        int r1 = std::stoi(pieces_match[1]);
        int r2 = std::stoi(pieces_match[2]);
        char target = std::string(pieces_match[3])[0];
        std::string token4 = pieces_match[4];

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
