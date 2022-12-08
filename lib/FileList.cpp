/*
 * FileList.cpp
 *
 *  Created on: 7 Dec 2022
 *      Author: vsilva1
 */

#include "FileList.h"

FileList::FileList(std::string path, FileList* parent, int size, bool directory) {
    this->path = path;
    this->directory = directory;
    this->size = size;
    this->parent = parent;
    if (size > 0 && parent != NULL){
        parent->setSize(size);
    }
    if (parent == NULL) this->root = this;
    else this->root = parent->getRoot();
}

FileList::~FileList() {
}

std::string FileList::getPath() {
    return path;
}

void FileList::setSize(int s) {
    size += s;
    if (parent != NULL) {
        parent->setSize(s);
    }
}

int FileList::getSize() {
    return size;
}

void FileList::setContent(std::string path, int size, bool directory) {
    contents.push_back(new FileList(path, this, size, directory));
}

std::vector<FileList*> FileList::getContents() {
    return contents;
}

FileList* FileList::getParent() {
    return parent;
}

FileList* FileList::getRoot() {
    return root;
}

