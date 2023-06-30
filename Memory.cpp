#include "headers/Memory.hpp"

MemoryManager& MemoryManager::GetInstance() {
    static MemoryManager manager;
    return manager;
}