#ifndef FILE_HPP
#define FILE_HPP

#include <bits/stdc++.h>
using namespace std;

class FileManager {

public:
    static FileManager& GetInstance();
};

class File {

public:
    string name;
    int offset;
    int size;

    File();
    File(string name, int offset, int size);
};

#endif
