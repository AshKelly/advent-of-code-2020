#include "../lib/aoc.h"

std::pair<int, int> find_seat(std::string boarding_pass) {
    int row = 0, col = 0;
    // Now we loop through the boarding pass
    for (int i = 0; i < boarding_pass.size(); i++) {
        if (boarding_pass[i] == 'F')
            row <<= 1;
        if (boarding_pass[i] == 'B') {
            row <<= 1;
            row += 1;
        }
        if (boarding_pass[i] == 'L')
            col <<= 1;
        if (boarding_pass[i] == 'R') {
            col <<= 1;
            col += 1;
        }
    }
    return {row, col};
}

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    // Load the boarding passes into a vector of strings
    std::pair<int, int> seat;
    int sum = 0, maxv = 0, minv = 100000, id = 0;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while (std::getline(myfile, line)) {
        seat = find_seat(line);
        id = seat.first * 8 + seat.second;

        minv = std::min(minv, id);
        maxv = std::max(maxv, id);
        sum += id;
    }
    myfile.close();

    // Expected sum
    ans1 = maxv;
    int expected = (maxv * (maxv + 1)) / 2 - ((minv) * (minv - 1)) / 2;
    ans2 = expected - sum;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
