#include <fstream>
#include <iostream>

#include <string>

#include <vector>

#include <regex>

int computer1(std::vector<std::pair<std::string, int>> &instructions) {
    std::vector<int> visited(instructions.size());
    int acc = 0;
    int i = 0;
    while (true) {
        if (i == instructions.size())
            return acc;

        visited[i] += 1;
        if (visited[i] == 2)
            return acc;

        if (instructions[i].first == "nop") {
            i++;
        } else if (instructions[i].first == "acc") {
            acc += instructions[i].second;
            i++;
        } else if (instructions[i].first == "jmp") {
            i += instructions[i].second;
        }
    }
    return 0;
}

int computer2(std::vector<std::pair<std::string, int>> &instructions,
              std::vector<int> &visited, int i) {
    while (true) {
        if (i == instructions.size())
            return 1;

        // We shouldn't reach here
        if (i > instructions.size()) {
            return -1;
        }

        // We've probably found an inf loop, let's break
        if (visited[i] > 0)
            return -1;
        visited[i] += 1;

        if (instructions[i].first == "nop") {
            i++;
        } else if (instructions[i].first == "acc") {
            i++;
        } else if (instructions[i].first == "jmp") {
            i += instructions[i].second;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::vector<std::pair<std::string, int>> instructions;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::regex pieces_regex("([a-z]{3}) ([+-]\\d*)");
    std::smatch pieces_match;
    while (std::getline(myfile, line)) {
        std::regex_search(line, pieces_match, pieces_regex);
        instructions.push_back({pieces_match[1], std::stoi(pieces_match[2])});
    }
    myfile.close();
    ans1 = computer1(instructions);

    // We must loop through and find the change in instruction that produces
    // the correct code
    std::vector<int> visited(instructions.size());
    int i = 0;
    while (i < instructions.size()) {
        ans2 == 0;
        // Try flipping the instruction
        if (instructions[i].first == "jmp") {
            ans2 = computer2(instructions, visited, i + 1);
        } else if (instructions[i].first == "nop") {
            ans2 = computer2(instructions, visited, i + instructions[i].second);
        }
        // Mark instruction as visited
        visited[i]++;
        // Have we found the good path?
        if (ans2 == 1)
            break;
        // Continue as if the instruction wasn't flipped
        if (instructions[i].first == "jmp")
            i += instructions[i].second;
        else
            i++;
    }

    /*
    int jmp_nop = 0;
    for(auto v : instructions)
        if (v.first != "acc")
            jmp_nop+=1;
    std::cout << jmp_nop << std::endl;

    int tot = 0;
    for(auto v : visited){
        tot += v;
    }
    std::cout << tot << std::endl;
    std::cout << visited.size() << std::endl;
    std::cout << i << std::endl;
    */

    // Fix instruction
    if (instructions[i].first == "jmp")
        instructions[i].first = "nop";
    else
        instructions[i].first = "jmp";

    // Re-run program
    ans2 = computer1(instructions);

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
