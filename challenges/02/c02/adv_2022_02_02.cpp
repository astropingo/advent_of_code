/*
 * adv_2022_02_02.cpp
 *
 *  Created on: 02 Dec 2022
 *      Author: vsilva1
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#define INPUT_FILE "challenges/02/input/vrs_02.txt"
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

    std::string s; //string buffer to read input file
    std::vector<int> results; //game results
    std::vector<int> mine; //my play
    std::vector<int> my_score; //my_score
    int answer = 0;

    input_file.open(INPUT_FILE, std::ios_base::in); //open file in read-only mode;
    if (read_ok() < 1) {
        std::cerr << "Error opening " << INPUT_FILE << "\n";
        input_file.close();
        return -1;
    }

    //store play for each player given by input_file:
    while (true) {
        input_file >> s;
        if (read_ok() < 1) { //eofbit || badbit || failbit
            input_file.close();
            break;
        }
        switch (*s.c_str()) {
        case 'A':
            results.push_back(1);
            break;
        case 'B':
            results.push_back(2);
            break;
        case 'C':
            results.push_back(3);
            break;
        case 'X':
            mine.push_back(1);
            break;
        case 'Y':
            mine.push_back(2);
            break;
        case 'Z':
            mine.push_back(3);
            break;
        default:
            std::cerr << "Invalid input: " << s << "\n";
        }
    }

    if (results.size() != mine.size()){
        std::cerr << "Error in vector sizes.\n";
        return -1;
    }

    //compute scores:
    std::vector<int>::iterator it1 = mine.begin();
    std::vector<int>::iterator it2 = results.begin();
    while (it1 != mine.end()){
        switch (*it1) {
        case 1:
            if (*it2 == 1) my_score.push_back(3);
            else if (*it2 == 2) my_score.push_back(1);
            else my_score.push_back(2);
            break;
        case 2:
            if (*it2 == 1) my_score.push_back(4);
            else if (*it2 == 2) my_score.push_back(5);
            else my_score.push_back(6);
            break;
        case 3:
            if (*it2 == 1) my_score.push_back(8);
            else if (*it2 == 2) my_score.push_back(9);
            else my_score.push_back(7);
            break;
        default:
            std::cerr << "Error in vector contents.\n";
            return -1;
        }
        it1++; it2++; answer += my_score.back();
    }

    std::cout << "answer: " << answer << std::endl;
    return 0;
}
