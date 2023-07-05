#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <bits/stdc++.h>
using namespace std;

class ProcessManager {

public:
    static ProcessManager& GetInstance();
};

class Process {
    
public:
    int PID;
    int priority;
    int memoffset;
    int size;
    bool printer;
    bool scanner;
    bool driver;

    Process ();
    Process( int ID,
             int CPUpriority,
             int offset,
             int block_size,
             bool print_use,
             bool scanner_use,
             bool driver_use );
};

#endif
