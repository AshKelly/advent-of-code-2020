#include "../lib/aoc.h"

class Field {
  public:
    std::string name;
    std::pair<int, int> range1;
    std::pair<int, int> range2;
    std::list<int> column;

    Field(std::string n, std::pair<int, int> r1, std::pair<int, int> r2)
        : name(n), range1(r1), range2(r2) {
    }

    int valid(int val) {
        if ((val >= range1.first) && (val <= range1.second)) {
            return 1;
        }
        if ((val >= range2.first) && (val <= range2.second)) {
            return 1;
        }
        return 0;
    }
};

int main(int argc, char *argv[]) {
    long int ans1 = 0, ans2 = 0;

    std::regex pieces_regex("([a-z\\s]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
    std::regex number("(\\d+)");

    std::fstream myfile("input", std::ios_base::in);

    // Load in the fields
    std::string line;
    std::smatch pieces_match;
    std::vector<Field> fields;
    while (std::getline(myfile, line)) {
        if (line == "")
            break;
        std::regex_search(line, pieces_match, pieces_regex);

        std::pair<int, int> r1 = {std::stoi(pieces_match[2]),
                                  std::stoi(pieces_match[3])};
        std::pair<int, int> r2 = {std::stoi(pieces_match[4]),
                                  std::stoi(pieces_match[5])};

        fields.push_back(Field(pieces_match[1], r1, r2));
    }

    // Now load in the tickets
    std::vector<std::vector<int>> tickets;
    while (std::getline(myfile, line)) {
        if ((line[0] == 'y') || (line[0] == 'n') || (line[0] == ' ') ||
            (line[0] == '\\'))
            continue;

        std::sregex_token_iterator it = {line.begin(), line.end(), number};

        std::vector<int> ticket;
        while (it != std::sregex_token_iterator()) {
            int n1 = std::stoi(*it);
            ticket.push_back(n1);
            it = std::next(it);
        }

        if (ticket.size() > 0)
            tickets.push_back(ticket);
    }
    myfile.close();

    // Loop through finding and marking invalid tickets
    std::vector<int> invalid(tickets.size());
    for (size_t i = 1; i < tickets.size(); i++) {
        std::vector<int> &t = tickets[i];
        for (auto v : t) {
            int valid = 0;
            // Check this number is valid for atleast 1 field
            for (auto &f : fields) {
                valid = std::max(valid, f.valid(v));
                if (valid == 1)
                    break;
            }
            // Add value and mark ticket as invalid, if invalid
            if (valid == 0) {
                ans1 += v;
                invalid[i] = 1;
            }
        }
    }

    // For each field we loop through and find every column for which the valid
    // tickets work
    // For each field
    for (size_t i = 0; i < fields.size(); i++) {
        // Try each column
        for (size_t j = 0; j < fields.size(); j++) {
            int valid = 1;
            // Try every valid ticket
            for (size_t k = 1; k < tickets.size(); k++) {
                if (invalid[k] == 1)
                    continue;
                valid *= fields[i].valid(tickets[k][j]);
                if (valid == 0)
                    break;
            }
            // Is this column a valid solution for this field?
            if (valid == 1)
                fields[i].column.push_back(j);
        }
    }

    // Each field knows it possibilities; now we need to work out every fields
    // column by a process of elimination. If one field has only 1 valid column
    // then its solved and that column cannot solve another field
    bool solved = false;
    while (!solved) {
        solved = true;
        for (auto &f : fields) {
            // Only one possibility, thus this field has its column and this
            // column cannot solve other fields so we remove it from their
            // possibilities
            if (f.column.size() == 1)
                for (auto &f2 : fields) {
                    if (f.name == f2.name)
                        continue;
                    f2.column.remove(f.column.front());
                }
            else
                solved = false;
        }
    }

    // Great, now every field knows which column it corresponds to! So we can
    // loop through our own ticket and multiply the values in columns with names
    // starting with departure
    ans2 = 1;
    for (auto &f : fields)
        if (f.name.substr(0, 9) == "departure")
            ans2 *= tickets[0][f.column.front()];

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
