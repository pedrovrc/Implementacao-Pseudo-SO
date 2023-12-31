#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <bits/stdc++.h>
using namespace std;


/*
    Class Process

    Classe que representa um processo no Pseudo-SO.
*/
class Process {
    bool isRunning;

public:
    int instructionCount;

    int PID;
    int startTime;
    int priority;
    int processingTime;
    int size;
    int printer;
    bool scanner;
    bool modem;
    int SATA;
    
    Process();
    void Reset();
    void PrintExecution();
    void ExecuteInstruction();
};

/*
    Class ProcessManager

    Classe que implementa o Gerenciador de Processos do Pseudo-SO.
    Possui uma lista de processos obtida pela leitura da entrada do sistema.
    Essa classe segue o padrão singleton.
*/
class ProcessManager {
    static ProcessManager* instance;

public:
    vector<Process> processList;
    int processCount;

    ProcessManager();
    static ProcessManager* GetInstance();
    void AddProcess(Process& in);
    bool ProcessExists(int PID);
    int GetListSize();
    void PrintList();
};

#endif
