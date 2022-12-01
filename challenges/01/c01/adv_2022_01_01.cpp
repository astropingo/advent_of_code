/*
 * adv_2022_01_01.cpp
 *
 *  Created on: 01 Dec 2022
 *      Author: vsilva1
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#define BUFFER_SIZE 81 //amount of characters read per line;

#define INPUT_FILE "challenges/01/input/vrs_01.txt"
std::fstream input_file;

int read_ok(){
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

    char c[BUFFER_SIZE]; //Character buffer for readline;
    std::vector<int> elf_supplies; //amount of calories carried by each elf.

    input_file.open(INPUT_FILE, std::ios_base::in); //open file in read-only mode;
    if (read_ok() < 1) {
        std::cerr << "Error opening " << INPUT_FILE << "\n";
        input_file.close();
        return -1;
    }

    //store supplies for each elf given by input_file:
    int counter = 0;
    elf_supplies.push_back(0);
    while (true){
        input_file.getline(c, BUFFER_SIZE);
        if (read_ok() < 0){ //eofbit || badbit
            input_file.close();
            break;
        } else if (*c){
            elf_supplies[counter] = elf_supplies[counter] + atoi(c);
        } else {
            elf_supplies.push_back(0);
            counter ++;
        }
    }

    int most_calories = 0;
    for (std::vector<int>::iterator it = elf_supplies.begin();
            it != elf_supplies.end(); it++){
        if (most_calories < *it) most_calories = *it;
    }

    std::cout << "answer: " << most_calories << std::endl;
    return 0;

}
