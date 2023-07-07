#include "headers/File.hpp"

FileManager& FileManager::GetInstance() {
    static FileManager manager;
    return manager;
}

void FileManager::AddFile(File& in) {
    fileList.push_back(in);
}

void FileManager::AddOperation(FSOperation& in) {
    operationList.push_back(in);
}

void FileManager::PrintFiles() {
    cout << "File List:" << endl;
    cout << "Total number of files: " << occupiedSegments << endl << endl;
    for (int i = 0; i < occupiedSegments; i++) {
        cout << "File name: " << fileList[i].name << endl;
        cout << "Offset: " << fileList[i].offset << endl;
        cout << "Size: " << fileList[i].size << endl;
        cout << "--------------------" << endl << endl;
    }
    cout << "------------ End of List ------------" << endl << endl;
}

void FileManager::PrintOperations() {
    cout << "Operation List:" << endl;
    cout << "Total number of operations: " << operationList.size() << endl << endl;
    for (int i = 0; i < operationList.size(); i++) {
        cout << "File name: " << operationList[i].PID << endl;
        cout << "Offset: " << operationList[i].opcode << endl;
        cout << "Size: " << operationList[i].filename << endl;
        cout << "Size: " << operationList[i].filesize << endl;
        cout << "--------------------" << endl << endl;
    }
    cout << "------------ End of List ------------" << endl << endl;
}

File::File() {
    name = "";
    offset = 0;
    size = 0;
}

FSOperation::FSOperation() {
    PID = 0;
    opcode = 0;
    filename = "";
    filesize = 0;
}
