#include "headers/Queue.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

QueueManager* QueueManager::instance;

QueueManager::QueueManager() {
    if (instance != nullptr) return;
    instance = this;
}

QueueManager* QueueManager::GetInstance() {
    if (instance == nullptr) {
		instance = new QueueManager();
	}
		return instance;
}
// ----------------------------------------------------

/*
    void QueueManager::AddProcessCreation(Process& in)

    Adiciona processo à fila de criação de processos.
*/
void QueueManager::AddProcessCreation(Process* in) {
    creationQueue.push_back(in);
}

/*
    void QueueManager::AddProcessExecution(Process& in)

    Adiciona processo a uma das filas de execução de processo.
    Prioridade == 0 -> Fila de Tempo Real
    Prioridade != 0 -> Fila de Usuário
*/
void QueueManager::AddProcessExecution(Process* in) {
    if (in->priority == 0) realTimeQueue.push_back(in);
    else userQueue.push_back(in);
}

/*
    void QueueManager::RemoveFromExecQueue(int PID, int priority)

    Remove o processo requisitado da fila de execução onde estiver.
*/
void QueueManager::RemoveFromExecQueue(int PID, int priority) {
    if (priority == 0) {
        // fila real time
        for (int i = 0; i < realTimeQueue.size(); i++) {
            if (realTimeQueue[i]->PID == PID) realTimeQueue.erase(realTimeQueue.begin() + i);
        }
    } else {
        // fila user
        for (int i = 0; i < userQueue.size(); i++) {
            if (userQueue[i]->PID == PID) userQueue.erase(userQueue.begin() + i);
        }
    }
}

/*
    Process* QueueManager::GetUserProcess()

    Retorna processo prioritário de acordo com política de escalonamento de múltiplas filas com realimentação.
*/
Process* QueueManager::GetUserProcess() {

}
