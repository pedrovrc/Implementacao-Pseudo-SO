#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <bits/stdc++.h>
using namespace std;

#include "Process.hpp"

/*
    Class QueueManager

    Classe responsável por implementar o Gerenciador de Filas do Pseudo-SO.
    Possui as filas de processos a serem gerenciadas durante a execução do sistema.
    Essa classe segue o padrão singleton.
*/
class QueueManager {
    static QueueManager* instance;
public:
    QueueManager();
    vector<Process*> creationQueue;
    vector<Process*> realTimeQueue;
    vector<Process*> userQueue;
    vector<Process*> userP1Queue;
    vector<Process*> userP2Queue;
    vector<Process*> userP3Queue;
    static QueueManager* GetInstance();
    void AddProcessCreation(Process* in);
    void AddProcessExecution(Process* in);
    void RemoveFromExecQueue(int PID, int priority);
    Process* GetUserProcess();
};

#endif
