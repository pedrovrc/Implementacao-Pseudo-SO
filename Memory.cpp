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
    return 0;
}

/*
    int MemoryManager::findSpace(int process_size)

    Retorna offset para segmento contíguo de tamanho suficiente para o requisitado pela entrada.
    Retorna -1 se não encontrar segmento contíguo grande o suficiente.
    (Essa função atualmente não está implementada)
*/
int MemoryManager::findSpace(int process_size) {
    return 0;
}
