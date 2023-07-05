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
    bool result = false;
    
    // le arquivo 1
    // armazena detalhes dos processos
    result = ReadProcesses(file1);
    if (result) {
        cout << "Arquivo de processos lido com sucesso" << endl;
    } else {
        cout << "Erro ao ler arquivo de processos" << endl;
        return false;
    }

    // le arquivo 2
    // atualiza estado do sistema de arquivos
    result = ReadFileSystem(file2);
    if (result) {
        cout << "Arquivo de sistema de arquivos lido com sucesso" << endl;
    } else {
        cout << "Erro ao ler arquivo de sistema de arquivos" << endl;
        return false;
    }
    
    // cria dispatcher

    // executa lista de processos em ordem
    
    // imprimir historico das operacoes do sistema de arquivos
    // imprimir mapa atual de ocupacao do disco
    
    return true;
}

bool PseudoOS::ReadProcesses(fstream* file) {
    return true;
}

bool PseudoOS::ReadFileSystem(fstream* file) {
    return true;
}
