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

std::pair<int, int> find_seat(std::string boarding_pass){
    std::pair<int, int> seat;
    int rowl = 0;
    int rowh = 127;
    int coll = 0;
    int colh = 7;

    for (int i=0; i<boarding_pass.size(); i++){
        if (boarding_pass[i] == 'F'){
            rowh = (rowl + rowh) / 2;
        }
        else if (boarding_pass[i] == 'B'){
            rowl = (rowl + rowh) / 2 + 1;
        }
        if (boarding_pass[i] == 'L'){
            colh = (coll + colh) / 2;
        }
        else if (boarding_pass[i] == 'R'){
            coll = (coll + colh) / 2 + 1;
        }
    }

    seat.first = rowl;
    seat.second = coll;

    return seat;
}


int main (int argc, char *argv[]){
    int ans1 = 0, ans2 = 0;

    // Load the boarding passes into a vector of strings
    std::vector<std::string> boarding_passes;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while(std::getline(myfile, line)){
        boarding_passes.push_back(line);
    }
    myfile.close();

    // Loop through and calculate the seat ids from the boarding passes
    std::vector<int> seat_ids;
    std::pair<int, int> seat;
    int id;
    for(auto bp : boarding_passes){
        seat = find_seat(bp);
        id = seat.first*8+seat.second;

        seat_ids.push_back(id);
        ans1 = std::max(ans1, id);
    }

    // Sort the seat ids
    std::sort(seat_ids.begin(), seat_ids.end());

    // Look for missing seat ids
    for(int i=1; i<seat_ids.size(); i++)
        if (seat_ids[i]-2 == seat_ids[i-1])
            ans2 = seat_ids[i]-1;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
