#include "../lib/aoc.h"

template <typename T>
std::set<T> intersection(std::set<T> &s1, std::set<T> &s2) {
    std::set<T> res;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                     std::inserter(res, res.begin()));
    return res;
}

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::vector<std::pair<std::set<std::string>, std::set<std::string>>> mylist;

    std::fstream myfile("input", std::ios_base::in);
    std::regex reg("([a-z]+)+");
    std::string line;
    while (std::getline(myfile, line)) {
        std::sregex_token_iterator it = {line.begin(), line.end(), reg};
        std::set<std::string> ingredients;
        std::set<std::string> allergens;
        while (it != std::sregex_token_iterator()) {
            if ((*it) == "contains") {
                it = std::next(it);
                break;
            }
            ingredients.insert(*it);
            it = std::next(it);
        }
        while (it != std::sregex_token_iterator()) {
            allergens.insert(*it);
            it = std::next(it);
        }
        mylist.push_back({ingredients, allergens});
    }
    myfile.close();

    // Store intersection of allergen triggers
    std::map<std::string, std::set<std::string>> allergen_possibilities;
    for (size_t i = 0; i < mylist.size(); i++) {
        std::set<std::string> &ingredients = mylist[i].first;
        std::set<std::string> &allergens = mylist[i].second;

        // Insert all the intersection of current ingredients, and the possible
        // allergen triggers
        for (auto &allergen : allergens)
            if (allergen_possibilities.find(allergen) !=
                allergen_possibilities.end())
                allergen_possibilities[allergen] =
                    intersection(ingredients, allergen_possibilities[allergen]);
            else
                allergen_possibilities[allergen] = ingredients;
    }

    // Count ingredients which aren't allergen possibilities
    for (size_t i = 0; i < mylist.size(); i++) {
        std::set<std::string> &ingredients = mylist[i].first;
        std::set<std::string> &allergens = mylist[i].second;

        // Check to see if each ingredient is an allergen or not, sum the
        // ingredients that are definitely not allergens
        for (auto &ingredient : ingredients) {
            bool found = false;
            for (auto &a_p : allergen_possibilities) {
                if (a_p.second.find(ingredient) != a_p.second.end())
                    found = true;
            }
            if (found == false)
                ans1++;
        }
    }

    // Print possibles
    std::cout << "Possibilities" << std::endl;
    std::cout << "=============" << std::endl;
    for (auto kv : allergen_possibilities) {
        std::cout << kv.first << ": ";
        for (auto ing : kv.second) {
            std::cout << ing << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Loop through and simulatenously solve for each allergen
    bool solved = false;
    while (!solved) {
        solved = true;
        for (auto &a_p : allergen_possibilities) {
            if (a_p.second.size() > 1) {
                solved = false;
            } else if (a_p.second.size() == 1) {
                for (auto &a_p2 : allergen_possibilities) {
                    if (a_p.first == a_p2.first)
                        continue;

                    std::set<std::string>::iterator it =
                        a_p2.second.find(*a_p.second.begin());

                    if (it != a_p2.second.end()) {
                        a_p2.second.erase(it);
                    }
                }
            }
        }
    }

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: ";
    // Print our answer
    for (auto &a_p : allergen_possibilities) {
        std::cout << *a_p.second.begin() << ",";
    }
    std::cout << std::endl;

    return 0;
}
