#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <bits/stdc++.h>
using namespace std;
#include "Process.hpp"

/*
    Class MemoryManager

    Classe que representa o Gerenciador de Memória do Pseudo-SO.
    É responsável por:
        - Alocar e liberar memória para processos;
        - Verificar presença ou ausência de processos em memória e fornecer seus offsets.
    Essa classe segue o padrão singleton.
*/
class MemoryManager {
    const int realTimeMemSize = 64;
    const int userMemSize = 960;
    int freeRTMem;
    int freeUserMem;
    vector<int> occupationMap;
    static MemoryManager* instance;

public:
    MemoryManager();
    static MemoryManager* GetInstance();
    int GetOffset(int PID);
    int FindSpace(Process p);
    void Allocate(Process p, int offset);
    void Free(int processSize, int offset);
};

#endif
