#include "../lib/aoc.h"

std::unordered_map<int, char> base_patterns;
std::unordered_map<int, std::vector<std::list<int>>> patterns;


bool check(std::string &s, std::list<int> &sequence){
    if ((s == "") || (sequence.size() == 0)){
        if ((s == "") && (sequence.size() == 0))
            return true;
        else
            return false;
    }

    std::unordered_map<int, char>::iterator it1 = base_patterns.find(sequence.front());
    if (it1 != base_patterns.end()){
        sequence.pop_front();
        if ((*it1).second == s[0]){
            std::string new_s = s.substr(1, s.size()-1);
            return check(new_s, sequence);
        }
        else
            return false;
    }
    else {
        std::unordered_map<int, std::vector<std::list<int>>>::iterator it2 = patterns.find(sequence.front());
        sequence.pop_front();
        for (auto t : (*it2).second){
            t.insert(t.end(), sequence.begin(), sequence.end());
            bool success = check(s, t);
            if (success)
                return true;
        }
        return false;
    }
}


int main (int argc, char *argv[]){
    int ans1 = 0, ans2 = 0;

    std::fstream myfile("input", std::ios_base::in);
    std::string line;

    while(std::getline(myfile, line)){
        int key = 0;
        int quote = 0, index = 0, last = 0;
        std::string pattern = "";
        
        if (line == "")
            break;

        std::vector<std::list<int>> all_indexes;
        std::list<int> indexes;
        for(size_t i=0; i<line.size(); i++){
            int ascii = int(line[i]);
            if (line[i] == ':')
                key = std::stoi(line.substr(0, i));
            else if (line[i] == ' '){
                if ((index > 0) && (last ==  -1))
                    indexes.push_back(std::stoi(line.substr(index+1, i-index-1)));
                index = i;
            }
            else if ((ascii >= 48) && (ascii <= 57)){
                last = -1;
                if (i == line.size()-1)
                    indexes.push_back(std::stoi(line.substr(index+1, i-index)));
            }
            else if (line[i] == '|'){
                all_indexes.push_back(indexes);
                indexes.clear();
                last = 0;
            }
            else if (line[i] == '"'){
                quote++;
                if (quote == 2)
                    pattern = line.substr(index+1, i-index-1);
                index = i;
            }
        }

        if (indexes.size() > 0)
            all_indexes.push_back(indexes);

        if (pattern != ""){
            base_patterns[key] = pattern[0];
        }
        else{
            patterns[key] = all_indexes;
        }
    }

    std::vector<std::string> targets;
    while(std::getline(myfile, line)){
        targets.push_back(line);
    }

    // Part 1
    for(auto t : targets){  
        std::list<int> sequence = {0};
        ans1 += int(check(t, sequence));
    }

    // Make recursive
    patterns[8] = {{42}, {42, 8}};
    patterns[11] = {{42, 31}, {42, 11, 31}};
    
    // Part 2
    for(auto t : targets){
        std::list<int> sequence = {0};
        ans2 += int(check(t, sequence));
    }

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
