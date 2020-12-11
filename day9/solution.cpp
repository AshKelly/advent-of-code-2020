#include "../lib/aoc.h"
#include <chrono>

int main(int argc, char *argv[]) {
    auto begin = std::chrono::high_resolution_clock::now();
    long int ans1 = 0, ans2 = 0;
    size_t preamble_max_size = 1000;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::list<long int> preamble;
    std::list<long int>::iterator it;
    std::unordered_map<long int, int> cached;
    std::unordered_map<long int, int>::iterator cached_it;

    while (std::getline(myfile, line)) {
        long int num = std::stol(line);

        if (preamble.size() == preamble_max_size) {
            // Can we find the pair of numbers which sum?
            bool found = false;
            it = preamble.begin();
            while (it != preamble.end()) {
                cached_it = cached.find(num - *it);
                if (cached_it != cached.end()) found = true;
                it = std::next(it);
            }

            if (found == false) {
                ans1 = num;
                break;
            }

            // Remove oldest value from preamble
            int rem = preamble.front();
            preamble.pop_front();

            // remove value from cache
            cached_it = cached.find(rem);
            if (cached_it != cached.end()){
                if ((*cached_it).second == 1)
                    cached.erase(cached_it);
                else{
                    (*cached_it).second--;
                }
            }
        }

        cached[num]++;
        preamble.push_back(num);
    }
    myfile.clear();
    myfile.seekg(0);

    //  Loop through keeping track of the longest subsequence <= to the target
    //  val
    std::list<long int> sequence;
    long int sum = 0;
    while (std::getline(myfile, line)) {
        // Add new number to sequence
        long int num = std::stol(line);
        sum += num;
        sequence.push_back(num);

        // If too large, remove some older values
        while (sum > ans1) {
            sum -= sequence.front();
            sequence.pop_front();
        }

        // Have we found the solution?
        if (sum == ans1)
            break;
    }
    myfile.close();

    // Find min and max of sequence
    long int smallest = sequence.front();
    long int largest = sequence.front();
    it = sequence.begin();
    while (it != sequence.end()) {
        smallest = std::min(*it, smallest);
        largest = std::max(*it, largest);
        it = std::next(it);
    }
    ans2 = largest + smallest;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    double runtime = (double) std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
    std::cout << runtime/1.e3 << " milli seconds" << std::endl;

    return 0;
}
