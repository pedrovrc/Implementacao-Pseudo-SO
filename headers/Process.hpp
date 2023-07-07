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
    bool modem;
    int disk;

    Process();
    void Reset();
    void PrintExecution();
};

class ProcessManager {
    vector<Process> processList;
    int processCount;
public:
    ProcessManager();
    static ProcessManager& GetInstance();
    void AddProcess(Process& in);
    bool ProcessExists(int PID);
    Process& GetProcess(int PID);
    int GetListSize();
    void PrintList();
};

#endif
