#include "headers/Memory.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

MemoryManager* MemoryManager::instance;

MemoryManager::MemoryManager() {
    if (instance != nullptr) return;
    instance = this;
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
int MemoryManager::findSpace(int PID, int process_size, int process_priority) {
    // indice do mapa de ocupação da memória
    int offset;
    // checa se processo deve ser alocado no segmento de real time ou de usuário
    if(process_priority == 0){
        // testa se há espaço em memória
        if(process_size <= freeRTMem){
            //posiciona o indice do vetor ao final do ultimo proceso alocado
            offset = realTimeMemSize - freeRTMem;
            // preenche o mapa de ocupacao com o ID do processo nos blocos ocupados
            for(int i = offset; i < process_size; i++){
                occupationMap[i] = PID;
            }
            // atualiza a memória disponível
            freeRTMem -= process_size;
             // retorna o offset do inicio do processo
            return (realTimeMemSize - (freeRTMem + process_size));
        }else{
            // Espaco insuficiente
            return -1;
        }
    }else{
         // testa se há espaço em memória
        if(process_size <= freeUserMem){
            //posiciona o indice do vetor ao final do ultimo proceso alocado (considerando que os primeiros 64 blocos sao reservados para Real time)
            offset = realTimeMemSize + userMemSize - freeUserMem;
            // preenche o mapa de ocupacao com o ID do processo nos blocos ocupados
            for(int i = offset; i < process_size; i++){
                occupationMap[i] = PID;
            }
             // atualiza a memória disponível
            freeUserMem -= process_size;
            // retorna o offset do inicio do processo
            return(userMemSize - (freeUserMem + process_size) + realTimeMemSize);
        }else{
            // Espaco insuficiente
            return -1;
        }
    }     
}
