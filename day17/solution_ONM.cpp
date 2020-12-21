#include "../lib/aoc.h"

const int MAX_IND = 1000;
const int HALF = 500;

void get_xyzw(long int key, int &x, int &y, int &z, int &w) {
    w = key % MAX_IND - HALF;
    key -= w;
    key /= MAX_IND;

    z = key % MAX_IND - HALF;
    key -= z;
    key /= MAX_IND;

    y = key % MAX_IND - HALF;
    key -= y;
    key /= MAX_IND;

    x = key - HALF;
}

long int key_xyzw(int x, int y, int z, int w) {
    long int key = x + HALF;
    key *= MAX_IND;
    key += y + HALF;
    key *= MAX_IND;
    key += z + HALF;
    key *= MAX_IND;
    key += w + HALF;
    return key;
}

int count_active_neighbours(std::unordered_map<long int, char> &world, int x,
                            int y, int z, int w) {
    std::unordered_map<long int, char>::iterator it;
    int active = 0;
    for (int xi = x - 1; xi <= x + 1; xi++)
        for (int yi = y - 1; yi <= y + 1; yi++)
            for (int zi = z - 1; zi <= z + 1; zi++)
                for (int wi = w - 1; wi <= w + 1; wi++) {
                    if ((xi == x) && (yi == y) && (zi == z) && (wi == w))
                        continue;

                    it = world.find(key_xyzw(xi, yi, zi, wi));
                    if (it != world.end())
                        active++;
                }

    return active;
}

int main(int argc, char *argv[]) {
    const int num_cycles = 6;
    int ans1 = 0, ans2 = 0;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    int lineno = 0;
    std::unordered_map<long int, char> world_initial;
    while (std::getline(myfile, line)) {
        for (size_t colno = 0; colno < line.size(); colno++)
            if (line[colno] == '#') {
                world_initial[key_xyzw(lineno, colno, 0, 0)] = 1;
            }
        lineno++;
    }
    myfile.close();

    std::unordered_map<long int, char> world = world_initial;
    std::unordered_map<long int, char>::iterator it;
    int x, y, z, w;
    for (int cycle = 1; cycle <= num_cycles; cycle++) {
        std::unordered_map<long int, char> new_world;
        int new_active = 0;

        for (auto cube : world) {
            get_xyzw(cube.first, x, y, z, w);

            for (int xi = x - 1; xi <= x + 1; xi++)
                for (int yi = y - 1; yi <= y + 1; yi++)
                    for (int zi = z - 1; zi <= z + 1; zi++) {
                        long int key = key_xyzw(xi, yi, zi, 0);
                        it = new_world.find(key);
                        if (it != new_world.end())
                            continue;

                        int active =
                            count_active_neighbours(world, xi, yi, zi, 0);

                        it = world.find(key);
                        if ((it != world.end()) &&
                                ((active == 3) || (active == 2)) ||
                            ((it == world.end()) && (active == 3))) {
                            new_world[key] = 1;
                            new_active++;
                        }
                    }
        }

        world = new_world;
        ans1 = new_active;
    }

    world = world_initial;
    for (int cycle = 1; cycle <= num_cycles; cycle++) {
        std::unordered_map<long int, char> new_world;
        int new_active = 0;

        for (auto cube : world) {
            get_xyzw(cube.first, x, y, z, w);

            for (int xi = x - 1; xi <= x + 1; xi++)
                for (int yi = y - 1; yi <= y + 1; yi++)
                    for (int zi = z - 1; zi <= z + 1; zi++)
                        for (int wi = w - 1; wi <= w + 1; wi++) {
                            long int key = key_xyzw(xi, yi, zi, wi);
                            it = new_world.find(key);
                            if (it != new_world.end())
                                continue;

                            int active =
                                count_active_neighbours(world, xi, yi, zi, wi);

                            it = world.find(key);
                            if ((it != world.end()) &&
                                    ((active == 3) || (active == 2)) ||
                                ((it == world.end()) && (active == 3))) {
                                new_world[key] = 1;
                                new_active++;
                            }
                        }
        }

        world = new_world;
        ans2 = new_active;
    }

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
