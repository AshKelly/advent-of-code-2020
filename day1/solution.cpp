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
    long int ans1 = 0, ans2 = 0;
    std::vector<int> numbers;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while (std::getline(myfile, line)) {
        numbers.push_back(std::stoi(line));
    }
    myfile.close();

    // Part 1
    for (long unsigned int i = 0; i < numbers.size(); i++)
        for (long unsigned int j = i + 1; j < numbers.size(); j++)
            if (numbers[i] + numbers[j] == 2020) {
                ans1 = numbers[i] * numbers[j];
                break;
            }

    // Part 2
    for (long unsigned int i = 0; i < numbers.size(); i++)
        for (long unsigned int j = i + 1; j < numbers.size(); j++)
            for (long unsigned int k = j + 1; k < numbers.size(); k++)
                if (numbers[i] + numbers[j] + numbers[k] == 2020) {
                    ans2 = numbers[i] * numbers[j] * numbers[k];
                    break;
                }

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
