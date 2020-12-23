#include "../lib/aoc.h"

int calculate_score(std::list<int> &deck) {
    int score = 0;
    int i = 1;
    std::list<int>::reverse_iterator it = deck.rbegin();
    while (it != deck.rend()) {
        score += (i++) * (*it);
        it = std::next(it);
    }
    return score;
}

int play_game1(std::list<int> deck1, std::list<int> deck2) {
    while ((deck1.size() > 0) && (deck2.size() > 0)) {
        int v1 = deck1.front();
        int v2 = deck2.front();
        deck1.pop_front();
        deck2.pop_front();

        if (v1 > v2) {
            deck1.push_back(v1);
            deck1.push_back(v2);
        } else if (v2 > v1) {
            deck2.push_back(v2);
            deck2.push_back(v1);
        }
    }

    if (deck1.size() > 0)
        return calculate_score(deck1);
    else
        return -calculate_score(deck2);
}

int play_recursive_combat(std::list<int> deck1, std::list<int> deck2) {
    std::map<std::list<int>, int> deck1_history = {};
    std::map<std::list<int>, int> deck2_history = {};

    while ((deck1.size() > 0) && (deck2.size() > 0)) {
        if ((deck1_history.find(deck1) != deck1_history.end()) &&
            (deck2_history.find(deck2) != deck2_history.end())) {
            return calculate_score(deck1);
        }
        deck1_history.insert({deck1, 1});
        deck2_history.insert({deck2, 1});

        int v1 = deck1.front();
        int v2 = deck2.front();
        deck1.pop_front();
        deck2.pop_front();

        if ((v1 <= int(deck1.size())) && (v2 <= int(deck2.size()))) {
            std::list<int> new_deck1 = {};
            std::list<int> new_deck2 = {};

            int max_val = 0;
            int max_holder = 0;
            std::list<int>::iterator it = deck1.begin();
            for (int i = 0; i < v1; i++) {
                new_deck1.push_back(*it);
                max_val = std::max(*it, max_val);
                it = std::next(it);
            }

            it = deck2.begin();
            for (int i = 0; i < v2; i++) {
                new_deck2.push_back(*it);
                if (*it > max_val) {
                    max_holder = 1;
                }
                it = std::next(it);
            }

            // In player 1 has the largest number in their deck then there is
            // no way they can lose a recursive game... If they player 2 has
            // the largest number they could lose due to the infinite loop rule
            int winner = 0;
            if (max_holder == 1)
                winner = play_recursive_combat(new_deck1, new_deck2);

            if (winner >= 0) {
                deck1.push_back(v1);
                deck1.push_back(v2);
            } else {
                deck2.push_back(v2);
                deck2.push_back(v1);
            }
        } else if (v1 > v2) {
            deck1.push_back(v1);
            deck1.push_back(v2);
        } else if (v2 > v1) {
            deck2.push_back(v2);
            deck2.push_back(v1);
        }
    }

    if (deck1.size() > 0)
        return calculate_score(deck1);
    else
        return -calculate_score(deck2);
}

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::list<int> deck1;
    std::list<int> deck2;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::getline(myfile, line);
    while (std::getline(myfile, line)) {
        if (line == "") {
            std::getline(myfile, line);
            break;
        }
        deck1.push_back(std::stoi(line));
    }
    while (std::getline(myfile, line)) {
        deck2.push_back(std::stoi(line));
    }
    myfile.close();

    ans1 = std::abs(play_game1(deck1, deck2));
    ans2 = std::abs(play_recursive_combat(deck1, deck2));

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
