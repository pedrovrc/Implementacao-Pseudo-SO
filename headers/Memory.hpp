#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <bits/stdc++.h>
using namespace std;

/*
    Class MemoryManager

    Classe que representa o Gerenciador de Memória do Pseudo-SO.
    Essa classe segue o padrão singleton.
*/
class MemoryManager {
    vector<int> occupationMap;
    static MemoryManager* instance;

public:
    MemoryManager();
    static MemoryManager* GetInstance();
    int GetOffset(int PID);
    int findSpace(int process_size);
};

#endif
