#include "../lib/aoc.h"

class Tile {
  public:
    int id;
    std::array<std::array<int, 10>, 10> contents;
    std::array<int, 4> neighbours;

    Tile(int i, std::array<std::array<int, 10>, 10> arr)
        : id(i), contents(arr) {
        neighbours.fill(-1);
    };

    std::array<int, 10> side(int nside) {
        // Get the array side 0:U, 1:D, 2:L, 3:R
        if (nside == 0)
            return contents[0];
        else if (nside == 1)
            return contents[9];
        else if (nside == 2) {
            std::array<int, 10> left;
            for (int i = 0; i < 10; i++)
                left[i] = contents[i][0];
            return left;
        } else {
            std::array<int, 10> right;
            for (int i = 0; i < 10; i++)
                right[i] = contents[i][9];
            return right;
        }
    }

    Tile flip_horizontal() {
        std::array<std::array<int, 10>, 10> arr = contents;
        for (auto &v : arr)
            std::reverse(v.begin(), v.end());
        return Tile(id, arr);
    }

    Tile flip_vertical() {
        std::array<std::array<int, 10>, 10> arr = contents;
        std::reverse(arr.begin(), arr.end());
        return Tile(id, arr);
    }

    Tile transpose() {
        std::array<std::array<int, 10>, 10> arr = contents;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                arr[i][j] = contents[j][i];
        return Tile(id, arr);
    }
};

std::vector<Tile> make_permuations(Tile tile) {
    // Generate the 8 permutations for each tile
    std::vector<Tile> tiles;
    for (auto t : {tile, tile.transpose()}) {
        tiles.push_back(t);
        tiles.push_back(t.flip_horizontal());
        tiles.push_back(t.flip_vertical());
        tiles.push_back(t.flip_vertical().flip_horizontal());
    }
    return tiles;
}

int are_neighbours(Tile &t1, Tile &t2, int side1, int side2, int ind,
                   int neigh) {
    // If we are neighbours, and we don't have neighbours then set us to be
    // neighbours
    if ((t1.side(side1) == t2.side(side2)) && (t1.neighbours[side1] == -1)) {
        t1.neighbours[side1] = neigh;
        t2.neighbours[side2] = ind;
        return 1;
    }
    // Else, return 0 and do nothing
    return 0;
}

void find_neighbours(std::vector<std::vector<Tile>> &tiles,
                     std::list<Tile> &processed_tiles, Tile &tile, int ind) {
    std::vector<std::pair<int, int>> side_pairs = {
        {0, 1}, {1, 0}, {2, 3}, {3, 2}};

    // Find unprocessed neighbours from rotated/flipped possibilites
    std::vector<std::vector<Tile>>::iterator it = tiles.begin();
    while (it != tiles.end()) {
        int neigh = processed_tiles.size();
        int found = 0;
        for (auto t : *it) {
            for (auto sp : side_pairs) {
                if (are_neighbours(tile, t, sp.first, sp.second, ind, neigh) >
                    0) {
                    processed_tiles.push_back(t);
                    found = 1;
                    break;
                }
            }
            if (found > 0)
                break;
        }
        // This tile is processed, we picked which permutation out of 8 we
        // needed, thus we can remove them
        if (found > 0)
            it = tiles.erase(it);
        else
            it = std::next(it);
    }

    // Find internal neighbours for the current neighbor
    int i = 0;
    for (auto &t : processed_tiles) {
        for (auto sp : side_pairs)
            are_neighbours(tile, t, sp.first, sp.second, ind, i);
        i++;
    }
}

std::vector<std::vector<Tile>> tile_grid(Tile current,
                                         std::list<Tile> processed_tiles) {
    int next_row, next_col;
    std::vector<std::vector<Tile>> rows;
    while (next_row != -1) {
        next_row = current.neighbours[1];
        next_col = current.neighbours[3];

        // Fill the row with the tiles
        std::vector<Tile> row;
        row.push_back(current);
        while (next_col != -1) {
            current = *std::next(processed_tiles.begin(), next_col);
            next_col = current.neighbours[3];
            row.push_back(current);
        }
        rows.push_back(row);

        // Move onto next row
        current = *std::next(processed_tiles.begin(), next_row);
    }
    return rows;
}

std::vector<std::string>
idenfity_monsters(std::vector<std::string> total_image) {
    for (size_t i = 0; i < total_image.size() - 2; i++) {
        for (size_t j = 0; j < total_image.size() - 19; j++) {
            bool monster = true;
            for (auto k : {18})
                if (total_image[i][j + k] != '#')
                    monster = false;
            for (auto k : {0, 5, 6, 11, 12, 17, 18, 19})
                if (total_image[i + 1][j + k] != '#')
                    monster = false;
            for (auto k : {1, 4, 7, 10, 13, 16})
                if (total_image[i + 2][j + k] != '#')
                    monster = false;

            if (monster == true) {
                for (auto k : {18})
                    total_image[i][j + k] = 'O';
                for (auto k : {0, 5, 6, 11, 12, 17, 18, 19})
                    total_image[i + 1][j + k] = 'O';
                for (auto k : {1, 4, 7, 10, 13, 16})
                    total_image[i + 2][j + k] = 'O';
            }
        }
    }
    return total_image;
}

std::vector<std::string>
generate_image_from_grid(std::vector<std::vector<Tile>> rows) {
    std::vector<std::string> total_image;
    for (size_t i = 0; i < rows.size(); i++) {
        for (size_t k = 1; k < 9; k++) {
            std::string img = "";
            for (size_t j = 0; j < rows[0].size(); j++) {
                for (size_t m = 1; m < 9; m++) {
                    if (rows[i][j].contents[k][m] == 1)
                        img += "#";
                    else
                        img += " ";
                }
            }
            total_image.push_back(img);
        }
    }
    return total_image;
}

int main(int argc, char *argv[]) {
    long int ans1 = 0, ans2 = 0;

    // Load the input and generate the permutations
    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    std::vector<std::vector<Tile>> tiles;
    std::list<Tile> processed_tiles;
    while (std::getline(myfile, line)) {
        if (line[0] == 'T') {
            int id = std::stoi(line.substr(5, 4));

            std::array<std::a1rray<int, 10>, 10> contents;
            for (auto &c : contents)
                c.fill(0);

            for (int j = 0; j < 10; j++) {
                std::getline(myfile, line);
                for (size_t i = 0; i < line.size(); i++)
                    if (line[i] == '#')
                        contents[j][i] = 1;
            }

            // If first tile, we will use this as our starting point
            if (processed_tiles.size() == 0)
                processed_tiles.push_back(Tile(id, contents));
            else
                tiles.push_back(make_permuations(Tile(id, contents)));
        }
    }
    myfile.close();

    // Loop through and find every tiles neighbours
    std::list<Tile>::iterator it = processed_tiles.begin();
    int ind = 0;
    while (it != processed_tiles.end()) {
        find_neighbours(tiles, processed_tiles, *it, ind++);
        it = std::next(it);
    }

    // Part 1: find the corner IDs
    ans1 = 1;
    Tile top_left = processed_tiles.front();
    for (auto &t : processed_tiles) {
        // Find the corners
        if ((std::min(t.neighbours[0], t.neighbours[1]) < 0) &&
            (std::min(t.neighbours[2], t.neighbours[3]) < 0))
            ans1 *= t.id;

        // Also find top left corner
        if ((t.neighbours[0] == -1) && (t.neighbours[2] == -1))
            top_left = t;
    }

    // Turn the list of tiles into a vector of tiles so we can access each
    // element easily by starting at top left and visiting the neighbours
    std::vector<std::vector<Tile>> rows = tile_grid(top_left, processed_tiles);

    // Turn the grid of tiles into vector of strings
    std::vector<std::string> image = generate_image_from_grid(rows);

    // Transform the image
    // Rotate the image 90 degrees
    std::vector<std::string> image_o = image;
    for (size_t i = 0; i < image.size(); i++)
        for (size_t j = 0; j < image.size(); j++)
            image[i][j] = image_o[j][i];

    // Attempt to identify monsters, again!
    image = idenfity_monsters(image);

    // Count '#'s
    for (size_t i = 0; i < image.size(); i++)
        for (size_t j = 0; j < image.size(); j++)
            if (image[i][j] == '#')
                ans2++;

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
