#ifndef PSEUDOOS_HPP
#define PSEUDOOS_HPP

#include <bits/stdc++.h>
using namespace std;

#include "File.hpp"
#include "Memory.hpp"
#include "Process.hpp"
#include "Queue.hpp"
#include "Resource.hpp"
#include "Dispatcher.hpp"

/*
    Class PseudoOS

    Classe que implementa o Pseudo-SO. Sua execução é dada pelo método Run.
    Essa classe segue o padrão singleton.
*/
class PseudoOS {
    static PseudoOS* instance;
    FileManager* fileManager;
    MemoryManager* memoryManager;
    ProcessManager* processManager;
    QueueManager* queueManager;
    ResourceManager* resourceManager;
    int currentProcessID;

    bool ReadProcessInput(fstream* file);
    bool ReadFileSystemInput(fstream* file);

public:
    PseudoOS();
    static PseudoOS& GetInstance();
    
    bool Run(fstream* file1, fstream* file2);
};

#endif
