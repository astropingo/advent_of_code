/*
 * FileList.h
 *
 *  Created on: 7 Dec 2022
 *      Author: vsilva1
 */

#ifndef LIB_INCLUDE_FILELIST_H_
#define LIB_INCLUDE_FILELIST_H_

#include <vector>
#include <string>

class FileList {
private:
    std::string path;
    bool directory;
    int size;
    std::vector<FileList*> contents;
    FileList* parent;
    FileList* root;

public:
    FileList(std::string path, FileList* parent, int size = 0, bool directory = false);
    ~FileList();
    std::string getPath();
    void setSize(int s);
    int getSize();
    void setContent(std::string path, int size = 0, bool directory = false);
    std::vector<FileList*> getContents();
    FileList* getParent();
    FileList* getRoot();

};

#endif /* LIB_INCLUDE_FILELIST_H_ */
