#include "../lib/aoc.h"

void get_active_range(std::map<std::array<int, 4>, char> &world, std::array<int, 8> &range){
    range.fill(0);
    for(auto kv : world){
        range[0] = std::min(kv.first[0]-1, range[0]);
        range[1] = std::max(kv.first[0]+1, range[1]);
        
        range[2] = std::min(kv.first[1]-1, range[2]);
        range[3] = std::max(kv.first[1]+1, range[3]);

        range[4] = std::min(kv.first[2]-1, range[4]);
        range[5] = std::max(kv.first[2]+1, range[5]);
        
        range[6] = std::min(kv.first[3]-1, range[6]);
        range[7] = std::max(kv.first[3]+1, range[7]);
    }
}


int count_active_neighbours(std::map<std::array<int, 4>, char> &world, int x, int y, int z, int w){
    std::map<std::array<int, 4>, char>::iterator it;
    int active = 0;
    for(int xi=x-1; xi<=x+1; xi++)
        for(int yi=y-1; yi<=y+1; yi++)
            for(int zi=z-1; zi<=z+1; zi++)
                for(int wi=w-1; wi<=w+1; wi++){
                    if((xi == x) && (yi == y) && (zi == z) && (wi == w))
                        continue;
                    it = world.find({xi, yi, zi, wi});
                    if (it != world.end())
                        active++;
                }

    return active;
}

int main (int argc, char *argv[]){
    int ans1 = 0, ans2 = 0;


    std::map<std::array<int, 4>, char> world_initial;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    int lineno = 0;
    while(std::getline(myfile, line)){
        for(size_t colno=0; colno<line.size(); colno++)
            if (line[colno] == '#') 
                world_initial[{lineno, int(colno), 0, 0}] = line[colno];
        lineno++;
    }
    myfile.close();

    // Part 1
    std::map<std::array<int, 4>, char> world = world_initial;
    std::map<std::array<int, 4>, char>::iterator it;
    std::array<int, 8> range;
    int num_cycles = 6;
    for(int cycle=1; cycle<=num_cycles; cycle++){
        get_active_range(world, range);
        std::map<std::array<int, 4>, char> new_world;

        int w = 0;
        int new_active = 0;
        for(int x=range[0]; x<=range[1]; x++) 
            for(int y=range[2]; y<=range[3]; y++) 
                for(int z=range[4]; z<=range[5]; z++){
                    it = world.find({x, y, z, w});
                    int active = count_active_neighbours(world, x, y, z, w);
                    // Active remain active
                    if ((it != world.end()) && ((active == 3) || (active == 2))){
                        new_world[{x, y, z, w}] = '#';
                        new_active++;
                    }
                    // Inactive to active
                    if ((it == world.end()) && (active == 3)){
                        new_world[{x, y, z, w}] = '#';
                        new_active++;
                    }
                }

        world = new_world;
        ans1 = new_active;
    }
    
    // Part 2
    world = world_initial;
    for(int cycle=1; cycle<=num_cycles; cycle++){
        get_active_range(world, range);
        std::map<std::array<int, 4>, char> new_world;

        int new_active = 0;
        for(int x=range[0]; x<=range[1]; x++) 
            for(int y=range[2]; y<=range[3]; y++) 
                for(int z=range[4]; z<=range[5]; z++)
                    for(int w=range[6]; w<=range[7]; w++){
                        it = world.find({x, y, z, w});
                        int active = count_active_neighbours(world, x, y, z, w);
                        // Active remain active
                        if ((it != world.end()) && ((active == 3) || (active == 2))){
                            new_world[{x, y, z, w}] = '#';
                            new_active++;
                        }
                        // Inactive to active
                        if ((it == world.end()) && (active == 3)){
                            new_world[{x, y, z, w}] = '#';
                            new_active++;
                        }
                }

        world = new_world;
        ans2 = new_active;
    }

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
