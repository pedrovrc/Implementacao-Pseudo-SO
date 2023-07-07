#include "headers/Memory.hpp"

MemoryManager& MemoryManager::GetInstance() {
    static MemoryManager manager;
    return manager;
}

int MemoryManager::GetOffset(int PID) {
    // encontrar processo em memoria, retornar offset
    return 0;
}
