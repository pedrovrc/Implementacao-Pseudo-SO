#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <bits/stdc++.h>
using namespace std;
#include "Process.hpp"

/*
    Class MemoryManager

    Classe que representa o Gerenciador de Memória do Pseudo-SO.
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
    int findSpace(Process p);
    void allocate(Process p, int offset);
    void free(int processSize, int offset);
};

#endif
