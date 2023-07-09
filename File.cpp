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

/*
    int FileManager::GetOffset(char fileID)

    Retorna offset do arquivo se ele for encontrado em disco.
    Retorna -1 caso contrário.
*/
int FileManager::GetOffset(char fileID) {
    for(int i = 0; i < occupationMap.size(); i++){
        if(occupationMap[i] == fileID){
            return i;
        }
    }
    return -1;
}

/*
    void FileManager::ExecuteFSOperation(int PID)

    Chamado por um processo ao executar uma instrução.
    Tenta executar uma operação no sistema de arquivos.
        - Olha lista de operações a serem feitas:
            - Caso primeira operação não tenha mesmo PID do processo que chamou, remove da lista (processo não existe)
            - Repete até encontrar uma operação com PID correspondente ou acabar a lista
            - Se encontrar, a executa e remove da lista.
            - Se não, não faz nada.
        - A cada operação removida da lista, notifica o Dispatcher para atualizar o histórico de operações.
*/
void FileManager::ExecuteFSOperation(int PID){
    string buffer;
    int offset;

    // busca operacao com PID correspondente ao do processo que chamou
    while(operationList[0].PID != PID && operationList.empty() == false){
        // enquanto não encontrar PID correspondente
        // seta operacao como falha por processo inexistente
        buffer = "";
        operationList[0].success = false;
        buffer += "Process " + to_string (operationList[0].PID) + " does not exist";
        operationList[0].reason = buffer;

        // notifica dispatcher para atualizar historico
        Dispatcher::GetInstance()->writeFSHistory(operationList[0]);

        // remove operacao da lista
        operationList.erase(operationList.begin());        
    }

    // reseta buffer
    buffer = "";

    // com PID correspondente, se houver operacao a ser feita
    if(operationList.empty() == false){
        // checa opcode
        // 0 -> criacao de arquivo
        // 1 -> delecao de arquivo
        if(operationList[0].opcode == 0){
            // verifica se ha espaco para criar arquivo em disco
            offset = FindSpace(operationList[0].filesize);

            // se houver
            if (offset != -1) {
                // aloca memoria para arquivo
                Allocate(operationList[0].filesize, offset, *operationList[0].filename.c_str());

                // define operacao como sucesso
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
            
            // senao
            }else{
                // operacao definida como falha por falta de espaco
                operationList[0].success = false;
                buffer += "Process " + to_string (operationList[0].PID) + " could not create file " + operationList[0].filename + " (not enough space)";
                operationList[0].reason = buffer;
            }
        }else{
            // verifica se arquivo existe em disco para poder deletar
            offset = GetOffset(*operationList[0].filename.c_str());

            // se existir
            if(offset != -1){
                // libera espaco de memoria onde o arquivo esta localizado
                Free(offset);

                // define operacao como sucesso
                operationList[0].success = true;
                buffer += "Process " + to_string (operationList[0].PID) + " deleted file "+ operationList[0].filename;
                operationList[0].reason = buffer;

            // senao
            }else{
                // define operacao como falha
                operationList[0].success = false;
                buffer += "Process " + to_string (operationList[0].PID) + "could not delete file "+ operationList[0].filename + "because it does not exist";
                operationList[0].reason = buffer;
            }
        }

        // notifica dispatcher para atualizar historico e remove operacao da lista
        Dispatcher::GetInstance()->writeFSHistory(operationList[0]);
        operationList.erase(operationList.begin());
    }   
}

/*
    int FileManager::FindSpace(int fileSize)

    Busca offset de segmento grande o suficiente para criacao de um arquivo dcom tamanho filesize.
    Retorna offset caso encontre, -1 caso não encontre.
*/
int FileManager::FindSpace(int fileSize) {
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

/*
    void FileManager::Allocate(int fileSize, int offset, char fileID)

    Preenche espaços de memória a partir de offset com o identificador do arquivo fornecido.
*/
void FileManager::Allocate(int fileSize, int offset, char fileID) {
    for (int i = offset; i < fileSize + offset; i++){
            occupationMap[i] = fileID;
    }        
}

/*
    void FileManager::Free(int offset)

    Apaga conteúdo de um arquivo em memória a partir do offset fornecido.
*/
void FileManager::Free(int offset) {
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
