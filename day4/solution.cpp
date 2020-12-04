#include <iostream>
#include <fstream>

#include <string>

#include <map>

#include <iterator>
#include <regex>


bool valididate_byr(std::map<std::string, std::string> &documents){
    int val = std::stoi(documents["byr"]);
    if ((val >= 1920) && (val <= 2002)) return true;
    return false;
}


bool valididate_eyr(std::map<std::string, std::string> &documents){
    int val = std::stoi(documents["eyr"]);
    if ((val >= 2020) && (val <= 2030)) return true;
    return false;
}


bool valididate_iyr(std::map<std::string, std::string> &documents){
    int val = std::stoi(documents["iyr"]);
    if ((val >= 2010) && (val <= 2020)) return true;
    return false;
}


bool valididate_hgt(std::map<std::string, std::string> &documents){
    const std::regex reg1("(^[0-9]{3}cm$)");
    const std::regex reg2("(^[0-9]{2}in$)");

    std::sregex_token_iterator it;
    it = {documents["hgt"].begin(), documents["hgt"].end(), reg1, 1};
    if(it != std::sregex_token_iterator()){
        int val = std::stoi(*it);
        if ((val >= 150) && (val <= 193)) return true;
    }

    it = {documents["hgt"].begin(), documents["hgt"].end(), reg2, 1};
    if(it != std::sregex_token_iterator()){
        int val = std::stoi(*it);
        if ((val >= 59) && (val <= 76)) return true;
    }

    return false;
}


bool valididate_hcl(std::map<std::string, std::string> &documents){
    const std::regex reg1("(^#[0-9a-f]{6}$)");
    std::sregex_token_iterator it;
    it = {documents["hcl"].begin(), documents["hcl"].end(), reg1, 1};
    if(it != std::sregex_token_iterator()) return true;
    return false;
}


bool valididate_ecl(std::map<std::string, std::string> &documents){
    const std::vector<std::string> ecls = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for (auto v : ecls)
        if (documents["ecl"] == v) return true;
    return false;
}


bool valididate_pid(std::map<std::string, std::string> &documents){
    const std::regex reg1("(^[0-9]{9}$)");
    std::sregex_token_iterator it;
    it = {documents["pid"].begin(), documents["pid"].end(), reg1, 1};
    if(it != std::sregex_token_iterator()) return true;
    return false;
}


int main (int argc, char *argv[]){
    int ans1 = 0, ans2 = 0;

    std::vector<std::string> required = {
        "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid",
    };

    std::fstream myfile("input", std::ios_base::in);
    std::string line;
    const std::regex reg("([a-z]+):([^\\s]+)");
    std::map<std::string, std::string> documents;
    while(std::getline(myfile, line)){
        std::sregex_token_iterator it = {line.begin(), line.end(), reg, {1, 2}};
        while(it != std::sregex_token_iterator()){
            std::string k = *it;
            it = std::next(it);
            std::string v = *it;
            documents[k] = v;
            it = std::next(it);
        }

        if (line == ""){
            bool valid = true;
            for(auto &k : required)
                if (documents[k] == "") valid = false;

            ans1 += valid;

            if (valid){
                valid *= valididate_byr(documents);
                valid *= valididate_iyr(documents);
                valid *= valididate_eyr(documents);
                valid *= valididate_hgt(documents);
                valid *= valididate_hcl(documents);
                valid *= valididate_ecl(documents);
                valid *= valididate_pid(documents);
                ans2 += valid;
            }

            documents.clear();
        }
    }
    myfile.close();

    std::cout << "Answer 1: " << ans1 << std::endl;
    std::cout << "Answer 2: " << ans2 << std::endl;

    return 0;
}
