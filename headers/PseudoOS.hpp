#ifndef PSEUDOOS_HPP
#define PSEUDOOS_HPP

#include <bits/stdc++.h>
using namespace std;

#include "File.hpp"
#include "Memory.hpp"
#include "Process.hpp"
#include "Queue.hpp"
#include "Resource.hpp"

class PseudoOS {
    FileManager fileManager;
    MemoryManager memoryManager;
    ProcessManager processManager;
    QueueManager queueManager;
    ResourceManager resourceManager;
    
public:
    PseudoOS();
    static PseudoOS& GetInstance();
    
    bool Run(fstream* file1, fstream* file2);
    bool ReadProcesses(fstream* file);
    bool ReadFileSystem(fstream* file);
};

#endif
