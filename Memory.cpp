#include "headers/Memory.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

MemoryManager* MemoryManager::instance;

MemoryManager::MemoryManager() {
    if (instance != nullptr) return;
    instance = this;
    freeRTMem = 64;
    freeUserMem = 960;
    for(int i=0; i < 1024; i++){
        occupationMap.push_back(-1);
    }
}

MemoryManager* MemoryManager::GetInstance() {
    if (instance == nullptr) {
		instance = new MemoryManager();
	}
		return instance;
}
// ----------------------------------------------------

/*
    int MemoryManager::GetOffset(int PID)

    Retorna o offset atual do processo se ele for encontrado em memória.
    Retorna -1 caso contrário.
    (Essa função atualmente não está implementada)
*/
int MemoryManager::GetOffset(int PID) {
    for(int i = 0; i < occupationMap.size(); i++){
        if(occupationMap[i] == PID){
            return i;
        }
    }
    return -1;
}

/*
    int MemoryManager::findSpace(int process_size)

    Retorna offset para segmento contíguo de tamanho suficiente para o requisitado pela entrada.
    Retorna -1 se não encontrar segmento contíguo grande o suficiente.
    (Essa função atualmente não está implementada)
*/
int MemoryManager::findSpace(Process p) {
    // checa se processo deve ser alocado no segmento de real time ou de usuário
    int sizeCounter = 0, offset = 0;
    if(p.priority == 0){
        for (int i = 0; i < realTimeMemSize; i++){
            if(occupationMap[i] != -1){
                offset = i+1;
                sizeCounter = 0;
                continue;
            } 
            sizeCounter++;
            if(sizeCounter == p.size)  return offset;
        }
        
    }else{
        offset = 64;
        for (int i = realTimeMemSize; i < (int)occupationMap.size(); i++){
            if(occupationMap[i] != -1){
                offset = i+1;
                sizeCounter = 0;
                continue;
            } 
            sizeCounter++;
            if(sizeCounter == p.size) return offset;
        }
    }// Espaco insuficiente
        return -1;    
}

void MemoryManager::allocate(Process p, int offset){
    for (int i = offset; i < p.size; i++){
            occupationMap[i] = p.PID;
    }        
}

void MemoryManager::free(int processSize, int offset){
    for (int i = offset; i < processSize; i++){
            occupationMap[i] = -1;
    }        
}
