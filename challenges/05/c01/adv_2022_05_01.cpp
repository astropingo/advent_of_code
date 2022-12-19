/*
 * adv_2022_05_01.cpp
 *
 *  Created on: 05 Dec 2022
 *      Author: vsilva1
 */
#include <cstdio>
#include <vector>

#define INPUT_FILE "challenges/05/input/vrs_05.txt"

int main(int argc, char **argv) {

    FILE *input_file;
    std::vector<char> s1, s2, s3, s4, s5, s6, s7, s8, s9;
    std::vector<std::vector<char>*> sp; //"stack pointer" to hold pointers to the stacks
    std::vector<char> aux;
    std::vector<int*> mv, from, to;
    char c = 'a';
    int read_status = 0;

    //initialize sp
    sp.push_back(&s1);
    sp.push_back(&s2);
    sp.push_back(&s3);
    sp.push_back(&s4);
    sp.push_back(&s5);
    sp.push_back(&s6);
    sp.push_back(&s7);
    sp.push_back(&s8);
    sp.push_back(&s9);

    //open file in read-only text mode
    input_file = fopen(INPUT_FILE, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening %s.\n", INPUT_FILE);
        return -1;
    }

    //store crates in reverse order:
    fgetc(input_file); //set initial position in the file.
    int idx = 0;
    while ((c = fgetc(input_file)) != '1'){
        if (idx > 8) idx = 0;
        if (c != ' ')
            sp[idx]->push_back(c);
        idx++;
        fgetc(input_file);
        fgetc(input_file);
        fgetc(input_file);
    }

    //revert vector order:
    for (int i = 0; i < 9; i++){
        aux = *(sp[i]);
        sp[i]->clear();
        int aux_size = aux.size();
        for (int j = 0; j < aux_size; j++){
            sp[i]->push_back((aux.back()));
            aux.pop_back();
        }
    }

    //setup file position to store moves:
    while (c != '\n')
        c = fgetc(input_file);
    fgetc(input_file);

    //store moves:
    while (true) {
        //allocate memory and read formated input to the correct vector positions
        mv.push_back(new int);
        from.push_back(new int);
        to.push_back(new int);
        read_status = fscanf(input_file, "move %d from %d to %d\n",
                mv.back(), from.back(), to.back());
        if (read_status == EOF) {
            //deallocate memory and delete unused last vector positions
            delete mv.back();
            delete from.back();
            delete to.back();
            mv.pop_back();
            from.pop_back();
            to.pop_back();
            break;
        } else if (read_status != 3) { //fail to read some of the arguments
            fclose(input_file);
            fprintf(stderr, "Error reading from: %s.\n", INPUT_FILE);
            fprintf(stderr, "read_status: %c.\n", c);
            return -1;
        }
    }

    //execute moves:
    for (int i = 0; i < from.size(); i++){
        for (int j = 0; j < *mv[i]; j++){
            sp[*to[i] - 1]->push_back(sp[*from[i] - 1]->back());
            sp[*from[i] - 1]->pop_back();
        }
    }

    fprintf(stdout, "answer: %c%c%c%c%c%c%c%c%c\n", s1.back(), s2.back(), s3.back(),
            s4.back(), s5.back(), s6.back(), s7.back(), s8.back(), s9.back());
    return 0;
}
