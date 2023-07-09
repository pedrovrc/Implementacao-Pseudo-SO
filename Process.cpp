#include "headers/Process.hpp"
#include "headers/Queue.hpp"
#include "headers/File.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

ProcessManager* ProcessManager::instance;

ProcessManager::ProcessManager() {
    if (instance != nullptr) return;
    instance = this;
    processCount = 0;
}

ProcessManager* ProcessManager::GetInstance() {
    if (instance == nullptr) {
		instance = new ProcessManager();
	}
		return instance;
}
// ----------------------------------------------------

/*
    void ProcessManager::AddProcess(Process& in)

    Se o número máximo de processos (1000) não tiver sido atingido, insere processo em processList.
    PID do processo é atribuído com base na contagem de processos atual, que é incrementada em seguida.
*/
void ProcessManager::AddProcess(Process& in) {
    if (processCount >= 1000) {
        cout << "Maximum number of processes reached!" << endl;
        return;
    }
    in.PID = processCount;
    processList.push_back(in);
    processCount++;
}

/*
    bool ProcessManager::ProcessExists(int PID)

    Retorna verdadeiro se processo com PID fornecido for encontrado na lista de processos.
    Retorna falso caso contrário.
*/
bool ProcessManager::ProcessExists(int PID) {
    for (int i = 0; i < processCount; i++) {
        if (processList[i].PID == PID) {
            return true;
        }
    }
    return false;
}

/*
    int ProcessManager::GetListSize()

    Retorna o tamanho de processList.
*/
int ProcessManager::GetListSize() {
    return processList.size();
}

/*
    void ProcessManager::PrintList()

    Imprime no terminal todos os processos contidos em processList.
    Criado para propósitos de debug.
*/
void ProcessManager::PrintList() {
    cout << "Process List:" << endl;
    cout << "Total number of processes: " << GetListSize() << endl << endl;
    for (int i = 0; i < GetListSize(); i++) {
        cout << "Process ID (PID): " << processList[i].PID << endl;
        cout << "Start time: " << processList[i].startTime << endl;
        cout << "Priority: " << processList[i].priority << endl;
        cout << "Processing time: " << processList[i].processingTime << endl;
        cout << "Size: " << processList[i].size << endl;
        cout << "Uses printer: " << processList[i].priority << endl;
        cout << "Uses scanner: " << processList[i].priority << endl;
        cout << "Uses driver: " << processList[i].priority << endl;
        cout << "Disk: " << processList[i].priority << endl;
        cout << "--------------------" << endl << endl;
    }
    cout << "------------ End of List ------------" << endl << endl;
}

Process::Process() {
    isRunning = false;
    instructionCount = 0;

    PID = 0;
    startTime = 0;
    priority = 0;
    processingTime = 0;
    size = 0;
    printer = false;
    scanner = false;
    modem = false;
    modem = false;
    disk = 0;
}

void Process::Reset() {
    PID = 0;
    startTime = 0;
    priority = 0;
    processingTime = 0;
    size = 0;
    printer = false;
    scanner = false;
    modem = false;
    modem = false;
    disk = 0;
}

/*
    void Process::PrintExecution()

    Simula uma execução completa do processo.
    Criado para propósitos de debug.
*/
void Process::PrintExecution() {
    cout << "process " << PID << " =>" << endl;
    for (int i = 0; i < processingTime; i++) {
        cout << "P" << PID << " instruction " << i+1 << endl;
    }
    cout << "P" << PID << " return SIGINT" << endl << endl;
}

/*
    void Process::ExecuteInstruction()

    Executa uma única instrução do processo a cada chamada, considerado o tempo de 1 quantum.
*/
void Process::ExecuteInstruction() {
    // se processo não estiver em execucao
    if (isRunning == false) {
        // print inicial
        cout << "process " << PID << " =>" << endl; 
        cout << "P" << PID << " STARTED" << endl;
        // muda flag e incrementa contador de instrucoes (iniciar prints em 1)
        isRunning = true;
        instructionCount++;
    }

    // se processo estiver em execucao e nao tiver concluido seu tempo
    if (instructionCount <= processingTime) {
        // print de instrucoes
        cout << "P" << PID << " instruction " << instructionCount << endl;
        FileManager::GetInstance()->ExecuteFSOperation(PID);
        instructionCount++;
    }

    if (instructionCount > processingTime) {
        // print final
        cout << "P" << PID << " return SIGINT" << endl << endl;
    }
}
