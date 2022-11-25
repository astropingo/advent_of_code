/*
 * day1-01.cpp
 *
 *  Created on: 23 Nov 2022
 *      Author: vsilva1
 */
#include <iostream>
#include <fstream>
#include <vector>

#define INPUT_FILE "challenges/01/input/input.txt"

int main(int argc, char **argv) {

    int a = 0;
    int increased = 0;
    std::vector<int> depths;
    std::fstream input_file;

    input_file.open(INPUT_FILE, std::ios_base::in); //open file in read-only mode;
    if (input_file.fail()) {
        std::cerr << "Error opening " << INPUT_FILE << "\n";
        goto file_error;
    }

    //store depths values from input_file in depths.
    do {
        input_file >> a;
        if (input_file.bad()) {
            std::cerr << "Error reading from " << INPUT_FILE << "\n";
            goto file_error;
        }
        depths.push_back(a);
    } while(input_file.good());
    input_file.close();

    //check if enough information was provided.
    if (depths.size() < 2) {
        std::cout << "Not enough depths in input file." << a << std::endl;
        return 0;
    }

    a = depths[0];
    //check if depth increased compared to the previous value.
    for (std::vector<int>::iterator it = depths.begin(); it != depths.end(); ++it) {
        if (*it > a)
            increased++;
        a = *it;
    }

    std::cout << "increased: " << increased << std::endl;
    return 0;

file_error:
    input_file.close();
    return 1;
}
