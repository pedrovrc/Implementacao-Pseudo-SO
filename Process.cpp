#include "headers/Process.hpp"

ProcessManager& ProcessManager::GetInstance() {
    static ProcessManager manager;
    return manager;
}