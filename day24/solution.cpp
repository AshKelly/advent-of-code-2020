#include "../lib/aoc.h"

// 0   1   2  3   4   5
// W, NW, NE, E, SE, SW
const std::vector<std::vector<std::pair<int, int>>> direction_offset = {
    {{+1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, +1}, {0, +1}},
    {{+1, 0}, {+1, -1}, {0, -1}, {-1, 0}, {0, +1}, {+1, +1}},
};

std::pair<int, int> calculate_neighbour_loc(std::pair<int, int> coord,
                                            int direction) {
    int parity = coord.second & 1;
    std::pair<int, int> dir = direction_offset[parity][direction];
    return {coord.first + dir.first, coord.second + dir.second};
}

int count_black(std::map<std::pair<int, int>, int> &grid) {
    int tot = 0;
    for (auto &kv : grid) {
        if (kv.second == 1)
            tot++;
    }
    return tot;
}

int erase_zeros(std::map<std::pair<int, int>, int> &grid) {
    for (auto it = grid.begin(); it != grid.end();) {
        if (it->second == 0)
            it = grid.erase(it);
        else
            ++it;
    }
    return 0;
}

std::map<std::pair<int, int>, int>
flip_tiles(std::map<std::pair<int, int>, int> grid) {
    std::map<std::pair<int, int>, int> new_grid = {};

    for (auto &kv : grid) {
        int black_neighbours = 0;

        // Test the neighbours of our currently black tile
        for (int j = 0; j < 6; j++) {
            // Get tile location
            std::pair<int, int> loc = calculate_neighbour_loc(kv.first, j);

            // If this is a black tile, skip, becuase we will test is seperately
            if (grid.find(loc) != grid.end()) {
                black_neighbours++;
                continue;
            }

            // Count black neighbours
            int neighbours = 0;
            for (int i = 0; i < 6; i++)
                if (grid.find(calculate_neighbour_loc(loc, i)) != grid.end()) {
                    neighbours += 1;
                    if (neighbours > 2)
                        break;
                }

            // Should we turn black?
            if (neighbours == 2)
                new_grid[loc] = 1;
        }

        // Test the current black tile
        if ((black_neighbours == 2) || (black_neighbours == 1))
            new_grid[kv.first] = 1;
    }

    return new_grid;
}

int main(int argc, char *argv[]) {
    int ans1 = 0, ans2 = 0;

    std::vector<std::vector<int>> directions;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    while (std::getline(myfile, line)) {
        std::vector<int> direction;
        size_t col = 0;
        while (col < line.size()) {
            if (line[col] == 'n') {
                col++;
                if (line[col] == 'w')
                    direction.push_back(1);
                else if (line[col] == 'e')
                    direction.push_back(2);
                col++;
            } else if (line[col] == 's') {
                col++;
                if (line[col] == 'w')
                    direction.push_back(5);
                else if (line[col] == 'e')
                    direction.push_back(4);
                col++;
            } else if (line[col] == 'w') {
                direction.push_back(0);
                col++;
            } else if (line[col] == 'e') {
                direction.push_back(3);
                col++;
            }
        }
        directions.push_back(direction);
    }
    myfile.close();

    // Flip tiles from input
    std::map<std::pair<int, int>, int> grid;
    for (auto direction : directions) {
        std::pair<int, int> loc = {0, 0};
        for (auto d : direction) {
            loc = calculate_neighbour_loc(loc, d);
        }
        grid[loc] ^= 1;
    }

    // This will make life a little easier
    erase_zeros(grid);

    ans1 = count_black(grid);

    // Flip 100 times
    for (int i = 0; i < 100; i++)
        grid = flip_tiles(grid);
    ans2 = count_black(grid);

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
