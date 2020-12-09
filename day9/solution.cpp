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


int main (int argc, char *argv[]){
    long int ans1 = 0, ans2 = 0;
    int preamble_max_size = 25;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::list<long int> preamble;
    std::list<long int>::iterator it;
    std::map<long int, long int> cached;
    while(std::getline(myfile, line)){
        long int num = std::stol(line);

        // Break if value not in cache
        if(preamble.size() == preamble_max_size){
            if (cached[num] == 0){
                ans1 = num;
                break;
            }

            // Remove oldest value from preamble, and it's contributions to the cache
            int rem = preamble.front();
            preamble.pop_front();
            it = preamble.begin();
            while (it != preamble.end()){
                cached[*it + rem]--;
                it = std::next(it);
            }
        }

        // Add new values contribution to cache, and then insert the new value to preamble
        it = preamble.begin();
        while (it != preamble.end()){
            cached[*it + num]++;
            it = std::next(it);
        }
        preamble.push_back(num);
    }
    myfile.clear();
    myfile.seekg(0);


    //  Loop through keeping track of the longest subsequence <= to the target val
    std::list<long int> sequence;
    long int sum = 0;
    while(std::getline(myfile, line)){
        // Add new number to sequence
        long int num = std::stol(line);
        sum += num;
        sequence.push_back(num);

        // If too large, remove some older values
        while (sum > ans1){
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
    while (it != sequence.end()){
        smallest = std::min(*it, smallest);
        largest = std::max(*it, largest);
        it = std::next(it);
    }
    ans2 = largest + smallest;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
