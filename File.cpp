#include "headers/File.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

FileManager* FileManager::instance;

FileManager::FileManager() {
    if (instance != nullptr) return;
    instance = this;
}

FileManager* FileManager::GetInstance() {
    if (instance == nullptr) {
		instance = new FileManager();
	}
		return instance;
}
// ----------------------------------------------------

/*
    void FileManager::AddFile(File& in)

    Adiciona objeto do tipo File no vetor fileList.
*/
void FileManager::AddFile(File& in) {
    fileList.push_back(in);
}

/*
    void FileManager::AddOperation(FSOperation& in)

    Adiciona objeto do tipo FSOperation no vetor operationList.
*/
void FileManager::AddOperation(FSOperation& in) {
    operationList.push_back(in);
}

/*
    void FileManager::PrintFiles()

    Imprime no terminal todos os arquivos presentes em fileList.
    Criado para propósitos de debug.
*/
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

/*
    void FileManager::PrintOperations()

    Imprime no terminal todas as operações presentes em operationList.
    Criado para propósitos de debug.
*/
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
    success = false;
    reason = "";
}
