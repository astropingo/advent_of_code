/*
 * adv_2022_04_02.cpp
 *
 *  Created on: 04 Dec 2022
 *      Author: vsilva1
 */
#include <cstdio>
#include <fstream>
#include <vector>

#define INPUT_FILE "challenges/04/input/vrs_04.txt"

int main(int argc, char **argv) {

    FILE *input_file;
    int read_status = 0;
    std::vector<int*> elf1;
    std::vector<int*> elf2;
    int answer = 0;

    input_file = fopen(INPUT_FILE, "r"); //open file in read-only mode;
    if (input_file == NULL) {
        fprintf(stderr, "Error opening %s.\n", INPUT_FILE);
        return -1;
    }

    //store id-number contents and evaluate answer
    while (true) {
        //allocate memory and read formated input to the correct vector positions
        elf1.push_back(new int[2]);
        elf2.push_back(new int[2]);
        read_status = fscanf(input_file, "%d-%d,%d-%d\n",
                elf1.back(), elf1.back()+1, elf2.back(), elf2.back()+1);
        if (read_status == EOF) {
            //deallocate memory and delete unused last vector positions
            delete []elf1.back();
            delete []elf2.back();
            elf1.pop_back();
            elf2.pop_back();
            break;
        } else if (read_status != 4) { //fail to read some of the arguments
            fclose(input_file);
            fprintf(stderr, "Error reading from: %s.\n", INPUT_FILE);
            return -1;
        } //evaluate limits
        if (elf1.back()[0] == elf2.back()[0] || elf1.back()[1] == elf2.back()[1])
            answer ++;
        else if (elf1.back()[0] < elf2.back()[0] &&
                (elf1.back()[1] > elf2.back()[1] || elf2.back()[0] <= elf1.back()[1]))
            answer++;
        else if (elf1.back()[0] > elf2.back()[0] &&
                (elf1.back()[1] < elf2.back()[1] || elf2.back()[1] >= elf1.back()[0]))
            answer++;
    }

    fprintf(stdout, "answer: %d.\n", answer);
    return 0;
}
