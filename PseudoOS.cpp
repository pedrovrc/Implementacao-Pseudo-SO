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
    // le arquivo 1
    // armazena detalhes dos processos

    // le arquivo 2
    // atualiza estado do sistema de arquivos
    
    // cria dispatcher

    // executa lista de processos em ordem
    
    // imprimir historico das operacoes do sistema de arquivos
    // imprimir mapa atual de ocupacao do disco
    return true;
}