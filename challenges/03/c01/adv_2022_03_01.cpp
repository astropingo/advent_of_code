/*
 * adv_2022_03_01.cpp
 *
 *  Created on: 03 Dec 2022
 *      Author: vsilva1
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#define BUFFER_SIZE 81 //amount of characters read per line;
#define NPOS std::string::npos //return value for substring not found

#define INPUT_FILE "challenges/03/input/vrs_03.txt"
std::fstream input_file;

int read_ok() {
    if (input_file.bad()) {
        std::cerr << "Error reading from " << INPUT_FILE << "\n";
        return -2;
    } else if (input_file.eof()) {
        std::cerr << "EOF: "<< INPUT_FILE << "\n";
        return -1;
    } else if (input_file.fail()) {
        std::cerr << "Fail to read input to variable." << "\n";
        return 0;
    }
    return 1;
}

int main(int argc, char **argv) {

    std::vector<char*> lines;
    int answer = 0;

    input_file.open(INPUT_FILE, std::ios_base::in); //open file in read-only mode;
    if (read_ok() < 1) {
        std::cerr << "Error opening " << INPUT_FILE << "\n";
        input_file.close();
        return -1;
    }

    //store rucksacks contents:
    while (true) {
        lines.push_back(new char[BUFFER_SIZE]);
        input_file.getline(lines.back(), BUFFER_SIZE);
        if (read_ok() < 1) { //eofbit || badbit || failbit
            input_file.close();
            break;
        }
    }
    lines.pop_back(); //remove last element because it shall be empty;

    //compute answer
    for (std::vector<char*>::iterator it1 = lines.begin();
            it1 != lines.end(); it1++){

        std::string s1 = std::string(*it1);
        std::string s2 = s1.substr(s1.length()/2, s1.length()/2);
        s1 = s1.substr(0, s1.length()/2);

        size_t pos = NPOS;
        for (std::string::iterator it2 = s1.begin();
                (it2 != s1.end() && pos == NPOS); it2++){
            pos = s2.find(*it2);
        }

        if (pos == NPOS) continue;
        islower(s2[pos]) ? answer += (s2[pos] - 96) : answer += (s2[pos] - 64 + 26);
    }

    std::cout << "answer: " << answer << std::endl;
    return 0;
}
