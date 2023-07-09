#ifndef FILE_HPP
#define FILE_HPP

#include <bits/stdc++.h>
using namespace std;

/*
    Class File

    Classe responsável por representar um arquivo no sistema de arquivos do Pseudo-SO.
*/
class File {

public:
    string name;
    int offset;
    int size;

    File();
};

/*
    Class FSOperation

    Classe responsável por representar uma operação sobre o sistema de arquivos.
*/
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

/*
    Class FileManager

    Classe responsável por atuar como Gerenciador de Arquivos do SO.
    Possui informações sobre o disco e os arquivos contidos nele, bem como operações que devem ser feitas sobre o sistema de arquivos.
    Essa classe segue o padrão singleton.
*/
class FileManager {
    static FileManager* instance;

public:
    vector<File> fileList;
    vector<FSOperation> operationList;
    vector<char> occupationMap;
    int diskSize;
    int occupiedSegments;

    FileManager();
    static FileManager* GetInstance();
    void AddFile(File& in);
    void AddOperation(FSOperation& in);
    void PrintFiles();
    void PrintOperations();
    void ExecuteFSOperation(int PID);
    int GetOffset(char fileID);
    int FindSpace(int fileSize);
    void Allocate(int fileSize, int offset, char FileID);
    void Free(int offset);
};

#endif
