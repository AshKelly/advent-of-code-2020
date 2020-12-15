#include "../lib/aoc.h"

int main (int argc, char *argv[]){
    int ans1 = 0, ans2 = 0;

    std::vector<int> starting = {0, 8, 15, 2, 12, 1, 4};
    int max_starting = int(starting.size());

    std::unordered_map<int, int> history;
    std::unordered_map<int, int>::iterator it;

    int index = 0;
    int num = starting[0];
    while (index < 30000000 - 1){
        it = history.find(num);
        if (it == history.end()){
            history.insert({num, index});
            num = 0;
        }
        else{
            num = (index - it->second);
            it->second = index;
        }
        index++;

        if (index < max_starting) num = starting[index];
        if (index == 2019) ans1 = num;
    }
    ans2 = num;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
