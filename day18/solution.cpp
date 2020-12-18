#include "../lib/aoc.h"


long int process_brackets(std::string subline, int part){
    // We are in a substring (..) where there are no brackets
    // except the start and end
    long int val = 0;
    long int num = 0;
    int mode = 0;
    int subindex = 0;
    char op =  '+';

    std::list<char> ops = {'+'};
    std::list<long int> nums = {0};
    for(size_t subletter=0; subletter<subline.size(); subletter++){
        // Process number
        int ascii = int(subline[subletter]);
        if ((ascii >= 48) && (ascii <= 59)){
            if (mode == 0){
                subindex = subletter;
                mode = 1;
            }
        }
        else if (mode == 1){
            num = std::stol(
                    subline.substr(subindex, subletter-subindex));
            // Part 1 just process in order
            if (op == '+')
                val += num;
            else if (op == '*')
                val *= num;

            // Part 2, store ops and process at the end, as we must do the
            // adds first!
            nums.push_back(num);
            ops.push_back(op);

            mode = 0;
        }

        if ((subline[subletter] == '+') ||
                (subline[subletter] == '*')){
            op = subline[subletter];
        }
    }

    if (part == 1)
        return val;
    else{
        std::list<char>::iterator op_it = ops.begin();
        std::list<long int>::iterator num_it = nums.begin();
        std::list<long int> products = {0};
        while(op_it != ops.end()){
            long int num1 = *num_it;
            op = *op_it;
            num_it = std::next(num_it);
            op_it = std::next(op_it);
            if (op == '*'){
                products.push_back(num1);
            }
            else{
                products.back() += num1;
            }
        }

        val = 1;
        for(auto v: products)
            if (v > 0)
                val *= v;

        return val;
    }
}


long int process_line(std::string line, int part){
    size_t letter = 0;
    int index = 0;
    // Loop through the line replacing the brackets
    while(letter < line.size()){
        if (line[letter] == '('){
            index = letter;
        }
        else if (line[letter] == ')'){
            // Identify subline as (...)
            std::string subline = line.substr(index, letter-index+1);

            // Process subline
            long int val = process_brackets(subline, part);

            // Replace the (...) with the number we have calcualted
            std::string nline = line.substr(0, index);
            nline += std::to_string(val);
            if (letter != line.size()-1)
                nline += line.substr(letter+1, line.size()-letter-1);
            line = nline;

            // We've removed the brackets and replaced with value inside, now
            // we start again at the beginning of the line until it has no
            // brackets
            letter = -1;
        }
        letter++;
    }
    line += " ";
    // Finally we have a line with no brackets, no we do all the steps in order
    long int val = process_brackets(line, part);
    return val;
}

int main (int argc, char *argv[]){
    long int ans1 = 0, ans2 = 0;
    std::fstream myfile("input", std::ios_base::in);
    std::string line;

    while(std::getline(myfile, line)){
        long int val1 = process_line(line, 1);
        long int val2 = process_line(line, 2);
        ans1 += val1;
        ans2 += val2;
    }
    myfile.close();

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
