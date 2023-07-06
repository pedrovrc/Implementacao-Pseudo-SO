#include "headers/File.hpp"

FileManager& FileManager::GetInstance() {
    static FileManager manager;
    return manager;
}

File::File() {
    name = "";
    offset = 0;
    size = 0;
}

File::File(string name, int offset, int size) {
    this->name = name;
    this->offset = offset;
    this->size = size;
}
