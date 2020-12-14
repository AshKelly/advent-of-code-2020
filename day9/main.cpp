#include <fstream>
#include <iostream>

#include <algorithm>
#include <chrono>
#include <list>
#include <vector>

using namespace std;

long mymin(long val1, long val2) {
    if (val1 > val2)
        return (val2);
    else
        return (val1);
}

long mymax(long val1, long val2) {
    if (val1 > val2)
        return (val1);
    else
        return (val2);
}

int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<long> data;
    string line;
    int inner = 0, pairs = 0, preamble = 25, datasize = 0;
    ;
    long int pt2min = 0, pt2max = 0, part1 = 0, part2 = 0, datai = 0, dataj = 0;

    // READ INPUT
    ifstream myfile("input");
    if (myfile.is_open()) {
        while (getline(myfile, line))
            data.push_back(std::stol(line, nullptr, 10));
        myfile.close();
    } else {
        cout << "Unable to open file";
        exit(1);
    }
    datasize = data.size();

    // PART 1
    for (int i = preamble; i < datasize; i++) {
        inner = i - preamble;
        pairs = 0;
        datai = data[i];
        for (int j = inner; j < i; j++) {
            dataj = data[j];
            for (int k = inner - 1; k < i; k++) {
                if (datai == dataj + data[k]) {
                    pairs++;
                    j = k = 999999999;
                }
            }
            inner = j + 2;
        }
        if (pairs == 0) {
            part1 = data[i];
            break;
        }
    }

    // PART 2
    for (int i = 0; i < datasize; i++) {
        part2 = 0;
        pt2min = 2520733884456010987;
        pt2max = 0;

        for (int j = i; j < datasize; j++) {
            part2 += data[j];
            pt2min = mymin(data[j], pt2min);
            pt2max = mymax(data[j], pt2max);
            if (part2 == part1) {
                part2 = pt2min + pt2max;
                i = j = 999999999;
            }
            if (part2 > part1)
                break;
        }
    }

    std::cout << "Part 1 answer = " << part1 << std::endl;
    std::cout << "Part 2 answer = " << part2 << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    double runtime =
        (double)std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                      begin)
            .count();
    std::cout << runtime / 1.e3 << " milli seconds" << std::endl;

    return 0;
}
