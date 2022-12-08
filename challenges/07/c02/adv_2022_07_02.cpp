/*
 * adv_2022_07_02.cpp
 *
 *  Created on: 07 Dec 2022
 *      Author: vsilva1
 */
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <FileList.h>

#define INPUT_FILE "challenges/07/input/vrs_07.txt"
#define BUFFER_SIZE 81

std::fstream input_file;
int read_ok(){
    if (input_file.bad()) {
        fprintf(stderr, "Error reading from %s.\n", INPUT_FILE);
        return -2;
    } else if (input_file.eof()) {
        fprintf(stderr, "EOF: %s.\n", INPUT_FILE);
        return -1;
    } else if (input_file.fail()) {
        fprintf(stderr, "Fail to read input to variable.\n");
        return 0;
    }
    return 1;
}

int execute_ls(FileList* &flp, char* buffer, std::vector<FileList*> &directories) {
    char buffer2[BUFFER_SIZE];
    int size;
    int read_status;
    while (true) {
        input_file.getline(buffer, BUFFER_SIZE);
        if ((read_status = read_ok()) < 1) break;
        if (buffer[0] == 'd') {
            sscanf(buffer, "dir %80s", buffer2);
            flp->setContent(std::string(buffer2), 0, true);
            directories.push_back(flp->getContents().back());
        } else {
            sscanf(buffer, "%d %80s", &size, buffer2);
            flp->setContent(std::string(buffer2), size, false);
        }
        if (input_file.peek() == '$') break;
    }
    return read_status;
}

void execute_cd(FileList* &flp, char* buffer) {
    char buffer2[BUFFER_SIZE];
    std::string path("..");
    std::vector<FileList*> contents = flp->getContents();
    std::vector<FileList*>::iterator it = contents.begin();
    sscanf(buffer, "%*s %*s %80s", buffer2);
    if (buffer2[0] == '/') flp = flp->getRoot();
    else if (!path.compare(buffer2))flp = flp->getParent();
    else {
        while (it != contents.end()) {
            path = (*it)->getPath();
            if(!path.compare(buffer2)) {
                flp = (*it);
                break;
            }
            it++;
        }
        if (it == contents.end()) {
            fprintf(stderr, "Did not found dir: %s\n", buffer2);
            exit(-1);
        }
    }
}

int main(int argc, char **argv) {

    char buffer[BUFFER_SIZE] = {0};
    std::string path;
    FileList* flp = new FileList(std::string(1, '/'), NULL, 0, true);
    std::vector<FileList*> directories;
    int answer = 0;

    directories.push_back(flp);
    //open file in read-only mode
    input_file.open(INPUT_FILE, std::ios_base::in);
    if (read_ok() < 1) {
        fprintf(stderr, "Error opening %s.\n", INPUT_FILE);
        input_file.close();
        return -1;
    }

    //parser
    while(true) {
        input_file.getline(buffer, BUFFER_SIZE);
        if (read_ok() < 1) break;
        if (buffer[0] == '$') { //command
            if (buffer[2] == 'l') { //ls
                if (execute_ls(flp, buffer, directories) < 1) break;
            } else if (buffer[2] == 'c') { //cd
                execute_cd(flp, buffer);
            } else {
                fprintf(stderr, "Command not found: %s\n", buffer);
                return -1;
            }
        } else {
            fprintf(stderr, "Command not found: %s\n", buffer);
        }
    }

    //which directory is closer to the necessary amount of space to be freed.
    int needed = 30000000 - 70000000 + flp->getRoot()->getSize();
    for (int i = 0; i < directories.size(); i++){
        if (needed < directories[i]->getSize()) {
            if (directories[i]->getSize() < directories[answer]->getSize())
            answer = i;
        }
    }

    fprintf(stdout, "answer: %d\n", directories[answer]->getSize());
    return 0;
}
