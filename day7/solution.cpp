#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <vector>
#include <map>
#include <set>
#include <list>

#include <algorithm>
#include <iterator>
#include <regex>

int main (int argc, char *argv[]){
    int ans1 = 0, ans2 = 0;


    std::map<std::string, std::vector<std::pair<std::string, int>>> rules;
    std::set<std::string> bags;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::smatch pieces_match;
    while (std::getline(myfile, line)) {
        // First I match the outer bag and what it contains
        std::regex pieces_regex("(.*) bags contain (.*)");
        std::regex_search(line, pieces_match, pieces_regex);
        // Outer bag is easy to process
        std::string container = pieces_match[1];
        rules[container] = {};

        // Then I loop through all of the bags it contains
        std::string contains = pieces_match[2];
        std::regex reg("(\\d+) ([a-z\\s]+) bag");
        std::sregex_token_iterator it = {contains.begin(), contains.end(), reg, {1, 2}};
        while (it != std::sregex_token_iterator()) {
            int num = std::stoi(*it);
            it = std::next(it);
            std::string type = *it;
            it = std::next(it);
            rules[container].push_back({type, num});
            bags.insert(type);
        }
        bags.insert(container);
    }
    myfile.close();

    // Part 1: how many different colour outer bags, contain a shiny gold bag?
    for(std::string ob : bags){
        if (ob == "shiny gold")
            continue;

        std::list<std::string> possible_bags = {ob};
        while (possible_bags.size() > 0){
            std::string b = possible_bags.front();

            // We found gold bag, lets move on
            if (b == "shiny gold"){
                ans1++;
                break;
            }

            // Add extra bags to check
            for(auto kv : rules[b]){
                possible_bags.push_back(kv.first);
            }

            possible_bags.pop_front();
        }
    }

    // Part 2: how many bags in a shiny gold bag?
    std::list<std::pair<std::string, int>> possible_bags;
    possible_bags.push_back({"shiny gold", 1});
    while (possible_bags.size() > 0){
        std::pair<std::string, int> b = possible_bags.front();
        ans2 += b.second;

        // Add extra bags to check
        for(auto kv : rules[b.first]){
            possible_bags.push_back({kv.first, kv.second*b.second});
        }

        possible_bags.pop_front();
    }

    // Remove initial shiny gold bag
    ans2--;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
