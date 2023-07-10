#include "headers/Dispatcher.hpp"
#include "headers/Memory.hpp"
#include "headers/File.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

Dispatcher* Dispatcher::instance;

Dispatcher::Dispatcher() {
    if (instance != nullptr) return;
    instance = this;
}

Dispatcher* Dispatcher::GetInstance() {
    if (instance == nullptr) {
		instance = new Dispatcher();
	}
		return instance;
}
// ----------------------------------------------------

/*
    void Dispatcher::PrintProcess(Process& proc)

    Imprime no terminal uma mensagem contendo informações sobre um processo.
*/
void Dispatcher::PrintProcess(Process& proc) {
    cout << "dispatcher =>" << endl;
    cout << "\tPID: " << proc.PID << endl;
    cout << "\toffset: " << MemoryManager::GetInstance()->GetOffset(proc.PID) << endl;
    cout << "\tblocks: " << proc.size << endl;
    cout << "\tpriority: " << proc.priority << endl;
    cout << "\ttime: " << proc.processingTime << endl;
    cout << "\tprinters: " << proc.printer << endl;
    cout << "\tscanners: " << proc.scanner << endl;
    cout << "\tmodems: " << proc.modem << endl;
    cout << "\tdrives: " << proc.SATA << endl;
    cout << endl;
}

void Dispatcher::writeFSHistory(FSOperation op){
    FSOperationHistory.push_back(op);
}

/*
    void Dispatcher::PrintOperationHistory()

    Imprime no terminal uma mensagem contendo o histórico de operações feitas no sistema de arquivos do Pseudo-SO.
*/
void Dispatcher::PrintOperationHistory() {    
    cout << "File System =>" << endl << endl;;

    for (int i = 0; i < FSOperationHistory.size(); i++) {
        if (FSOperationHistory[i].success) {
            cout << "Operation " << i << " => Success" << endl;
        } else {
            cout << "Operation " << i << " => Failed" << endl;
        }

        cout << FSOperationHistory[i].reason << endl << endl;
    }
    cout << endl;
}

/*
    void Dispatcher::PrintFileSystemState()

    Imprime no terminal uma mensagem contendo o estado atual do disco do Pseudo-SO.
*/
void Dispatcher::PrintFileSystemState() {
    FileManager* fileManager = fileManager->GetInstance();
    
    cout << "Disk occupation map:" << endl;
    cout << "| ";
    for (int i = 0; i < fileManager->diskSize; i++) {
        if (fileManager->occupationMap[i] != '0') {
            cout << fileManager->occupationMap[i] << " | ";
        } else {
            cout << "  | ";
        }
    }
    cout << endl << endl;
}
