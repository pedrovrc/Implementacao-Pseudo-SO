#include "headers/File.hpp"
#include "headers/Dispatcher.hpp"

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

int FileManager::GetOffset(char fileID) {
    for(int i = 0; i < occupationMap.size(); i++){
        if(occupationMap[i] == fileID){
            return i;
        }
    }
    return -1;
}

void FileManager::ExecuteFSOperation(int PID){
    string buffer;
    int offset;
    while(operationList[0].PID != PID && operationList.empty() == false){
        buffer = "";
        operationList[0].success = false;
        buffer += "Process " + to_string (operationList[0].PID) + " does not exist";
        operationList[0].reason = buffer;
        Dispatcher::GetInstance()->writeFSHistory(operationList[0]);
        operationList.erase(operationList.begin());        
    }
    buffer = "";
    if(operationList.empty() == false){
        if(operationList[0].opcode == 0){
            offset = findSpace(operationList[0].filesize);
            if (offset != -1) {
                allocate(operationList[0].filesize, offset, *operationList[0].filename.c_str());
                operationList[0].success = true;
                buffer += "Process " + to_string (operationList[0].PID) + " created file " + operationList[0].filename + " (blocks ";
                for(int i= 0; i < operationList[0].filesize; i++ ){
                    buffer += to_string (offset+i);
                    if(i == operationList[0].filesize - 2){
                        buffer += " and ";  
                    }else if(i != operationList[0].filesize - 1){
                        buffer += ", "; 
                    }
                }
                buffer += ")";
                operationList[0].reason = buffer;
            }else{
                operationList[0].success = false;
                buffer += "Process " + to_string (operationList[0].PID) + " could not create file " + operationList[0].filename + " (not enough space)";
                operationList[0].reason = buffer;
            }
        }else{
            offset = GetOffset(*operationList[0].filename.c_str());
            if(offset != -1){
                free(offset);
                operationList[0].success = true;
                buffer += "Process " + to_string (operationList[0].PID) + " deleted file "+ operationList[0].filename;
                operationList[0].reason = buffer;
            }else{
                operationList[0].success = false;
                buffer += "Process " + to_string (operationList[0].PID) + "could not delete file "+ operationList[0].filename + "because it does not exist";
                operationList[0].reason = buffer;
            }
        }
        Dispatcher::GetInstance()->writeFSHistory(operationList[0]);
        operationList.erase(operationList.begin());
    }   
}

int FileManager::findSpace(int fileSize) {
    // checa se processo deve ser alocado no segmento de real time ou de usuário
    int sizeCounter = 0, offset = 0;
        for (int i = 0; i < occupationMap.size(); i++){
            if(occupationMap[i] != '0'){
                offset = i+1;
                sizeCounter = 0;
                continue;
            } 
            sizeCounter++;
            if(sizeCounter == fileSize)  return offset;
        }
        return -1;    
}

void FileManager::allocate(int fileSize, int offset, char fileID){
    for (int i = offset; i < fileSize + offset; i++){
            occupationMap[i] = fileID;
    }        
}

void FileManager::free(int offset){
    int i = offset;
    char name = occupationMap[i];
    while (occupationMap[i] == name) {
        occupationMap[i] = '0';
        i++;
    }    
}


File::File(){
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
