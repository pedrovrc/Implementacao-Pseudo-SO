#ifndef FILE_HPP
#define FILE_HPP

#include <bits/stdc++.h>
using namespace std;

class File {

public:
    string name;
    int offset;
    int size;

    File();
};

class FSOperation {

public:
    int PID;
    bool opcode;
    string filename;
    int filesize;
    bool success;
    string reason;

    FSOperation();
};

class FileManager {

public:
    vector<File> fileList;
    vector<FSOperation> operationList;
    vector<bool> bitMap;
    int diskSize;
    int occupiedSegments;

    static FileManager& GetInstance();
    void AddFile(File& in);
    void AddOperation(FSOperation& in);
    void PrintFiles();
    void PrintOperations();
};

#endif
