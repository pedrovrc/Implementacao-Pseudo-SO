#include "headers/PseudoOS.hpp"

PseudoOS::PseudoOS() {
    fileManager = fileManager.GetInstance();
    memoryManager = memoryManager.GetInstance();
    processManager = processManager.GetInstance();
    queueManager = queueManager.GetInstance();
    resourceManager = resourceManager.GetInstance();
}

PseudoOS& PseudoOS::GetInstance() {
    static PseudoOS system;
    return system;
}

bool PseudoOS::Run (fstream* file1, fstream* file2) {
    // codigo vai aqui
    return true;
}