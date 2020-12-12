#include "../lib/aoc.h"

int process_step1(std::vector<std::vector<char>> &mymap,
                  std::vector<std::vector<char>> &mymap_new) {
    /*
     * If a seat is empty (L) and there are no occupied seats adjacent to it,
     * the seat becomes occupied.  If a seat is occupied (#) and four or more
     * seats adjacent to it are also occupied, the seat becomes empty.
     * Otherwise, the seat's state does not change.
     */
    int total_occ = 0;
    for (size_t i = 0; i < mymap.size(); i++) {
        for (size_t j = 0; j < mymap[0].size(); j++) {
            if (mymap[i][j] == '.')
                continue;

            // What range of neighbours to check?
            int li = std::max(int(i) - 1, 0);
            int lj = std::max(int(j) - 1, 0);
            int hi = std::min(i + 2, mymap.size());
            int hj = std::min(j + 2, mymap[0].size());
            int occ = 0;
            for (int ni = li; ni < hi; ni++) {
                for (int nj = lj; nj < hj; nj++) {
                    if (mymap[ni][nj] == '#')
                        occ++;
                }
            }

            if ((mymap[i][j] == '#') && (occ >= 5))
                mymap_new[i][j] = 'L';
            if ((mymap[i][j] == 'L') && (occ == 0))
                mymap_new[i][j] = '#';
            if (mymap_new[i][j] == '#')
                total_occ++;
        }
    }
    return total_occ;
}

int process_step2(std::vector<std::vector<char>> &mymap,
                  std::vector<std::vector<char>> &mymap_new) {
    // 8 directions
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    int total_occ = 0;
    for (size_t i = 0; i < mymap.size(); i++) {
        for (size_t j = 0; j < mymap[0].size(); j++) {
            if (mymap[i][j] == '.')
                continue;

            // Fire out rays in all 8 directions
            int occ = 0;
            for (auto dir : directions) {
                std::pair<int, int> start = {i, j};
                start.first += dir.first;
                start.second += dir.second;

                while ((start.first >= 0) &&
                       (start.first < int(mymap.size())) &&
                       (start.second >= 0) &&
                       (start.second < int(mymap[0].size()))) {
                    if (mymap[start.first][start.second] == 'L')
                        break;
                    else if (mymap[start.first][start.second] == '#') {
                        occ++;
                        break;
                    }
                    start.first += dir.first;
                    start.second += dir.second;
                }
            }

            // What should be do to the map?
            if ((mymap[i][j] == '#') && (occ >= 5))
                mymap_new[i][j] = 'L';
            if ((mymap[i][j] == 'L') && (occ == 0))
                mymap_new[i][j] = '#';
            if (mymap_new[i][j] == '#')
                total_occ++;
        }
    }
    return total_occ;
}

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::vector<std::vector<char>> mymap;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while (std::getline(myfile, line)) {
        std::vector<char> l;
        for (auto c : line)
            l.push_back(c);
        mymap.push_back(l);
    }
    myfile.close();

    int occ = 0;
    int last_occ = 1;

    // Loop until convergence
    std::vector<std::vector<char>> mymap_old = mymap;
    std::vector<std::vector<char>> mymap_new = mymap;
    while (occ != last_occ) {
        last_occ = occ;
        mymap_old = mymap_new;
        occ = process_step1(mymap_old, mymap_new);
    }
    ans1 = occ;

    // Reset the maps and counters
    occ = 0;
    last_occ = 1;
    mymap_old = mymap;
    mymap_new = mymap;

    // Loop until convergence
    while (occ != last_occ) {
        last_occ = occ;
        mymap_old = mymap_new;
        occ = process_step2(mymap_old, mymap_new);
    }
    ans2 = occ;
    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
