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
void QueueManager::AddProcessCreation(Process& in) {
    creationQueue.push_back(in);
}

/*
    void QueueManager::AddProcessExecution(Process& in)

    Adiciona processo a uma das filas de execução de processo.
    Prioridade == 0 -> Fila de Tempo Real
    Prioridade != 0 -> Fila de Usuário
*/
void QueueManager::AddProcessExecution(Process& in) {
    if (in.priority == 0) realTimeQueue.push_back(in);
    else userQueue.push_back(in);
}

/*
    Process* QueueManager::GetUserProcess()

    Retorna processo prioritário de acordo com política de escalonamento de múltiplas filas com realimentação.
*/
Process* QueueManager::GetUserProcess() {

}
