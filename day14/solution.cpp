#include "../lib/aoc.h"

int main(int argc, char *argv[]) {
    long unsigned int ans1 = 0, ans2 = 0;

    std::fstream myfile("input", std::ios_base::in);
    std::map<long unsigned int, long unsigned int> memory_ans1;
    std::map<long unsigned int, long unsigned int> memory_ans2;

    const std::regex reg1("mask = ([X0-1]+)");
    const std::regex reg2("mem\\[([0-9]+)] = ([0-9]+)");
    std::string line;
    std::smatch pieces_match;

    unsigned long int or_mask = 0;
    unsigned long int and_mask = ~or_mask;
    unsigned long int either_mask = 0;
    unsigned long int one = 1;
    while (std::getline(myfile, line)) {
        if (line[1] == 'a') {
            // Reload the mask
            std::regex_search(line, pieces_match, reg1);
            std::string mask = pieces_match[1];

            // Make or + and + either components
            or_mask = 0;
            either_mask = 0;
            and_mask = ~or_mask;
            for (size_t i = 0; i < mask.size(); i++) {
                if (mask[mask.size() - 1 - i] == '1')
                    or_mask += (one << i);
                else if (mask[mask.size() - 1 - i] == '0')
                    and_mask -= (one << i);
                else if (mask[mask.size() - 1 - i] == 'X')
                    either_mask += (one << i);
            }

        } else {
            std::regex_search(line, pieces_match, reg2);
            unsigned long int num1 = std::stoull(pieces_match[1]);
            unsigned long int num2 = std::stoull(pieces_match[2]);

            // Put masked value into first answer map
            memory_ans1[num1] = ((num2 & and_mask) | or_mask);

            // Generate all possible memory addresses
            std::vector<long unsigned int> addresses;
            addresses.push_back(((num1 | or_mask) & (~either_mask)));
            for (unsigned long int i = 0; i < 36; i++) {
                if (((either_mask >> i) & one) > 0) {
                    size_t maxj = addresses.size();
                    for (size_t j = 0; j < maxj; j++) {
                        addresses.push_back(addresses[j] + (one << i));
                    }
                }
            }

            // Put value into possible addresses
            for (auto v : addresses)
                memory_ans2[v] = num2;
        }
    }
    myfile.close();

    ans1 = 0;
    for (auto kv : memory_ans1)
        ans1 += kv.second;

    ans2 = 0;
    for (auto kv : memory_ans2)
        ans2 += kv.second;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
