/*
 * adv_2022_03_02.cpp
 *
 *  Created on: 03 Dec 2022
 *      Author: vsilva1
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

size_t find_next_common_c(std::string &s1, std::string &s2, size_t &pos1) {
    if (pos1 > 0) pos1++;
    size_t pos2 = NPOS;
    while (pos1 < s1.size() && pos2 == NPOS){
        pos2 = s2.find(s1[pos1++]);
    }
    if (pos2 == NPOS) return s1.size();
    return pos1 - 1;
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
    if (lines.size() % 3) {
        std::cerr << "#lines not divisable by 3. Check input file: " << INPUT_FILE << "\n";
        return -1;
    }

    //compute answer
    for (std::vector<char*>::iterator itl = lines.begin();
            itl != lines.end();){

        std::string s1 = std::string(*(itl++));
        std::string s2 = std::string(*(itl++));
        std::string s3 = std::string(*(itl++));

        size_t pos1 = 0;
        size_t pos2 = NPOS;
        do {
            pos1 = find_next_common_c(s1, s2, pos1);
            if (pos1 == s1.size()) {
                std::cerr << "Could not find common item.\n";
                return -1;
            }
            pos2 = s3.find(s1[pos1]);
        } while (pos2 == NPOS);
        islower(s1[pos1]) ? answer += (s1[pos1] - 96) : answer += (s1[pos1] - 64 + 26);
    }

    std::cout << "answer: " << answer << std::endl;
    return 0;
}
