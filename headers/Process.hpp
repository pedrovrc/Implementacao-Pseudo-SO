#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <bits/stdc++.h>
using namespace std;

class Process {
    
public:
    int PID;
    int startTime;
    int priority;
    int processingTime;
    int size;
    bool printer;
    bool scanner;
    bool driver;
    int disk;

    Process();
    void Reset();
};

class ProcessManager {
    vector<Process> processList;
    int processCount;
public:
    ProcessManager();
    static ProcessManager& GetInstance();
    void AddProcess(Process& in);
    int GetListSize();
    void PrintList();
};

#endif
