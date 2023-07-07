#include "headers/Process.hpp"

ProcessManager::ProcessManager() {
    processCount = 0;
}

ProcessManager& ProcessManager::GetInstance() {
    static ProcessManager manager;
    return manager;
}

void ProcessManager::AddProcess(Process& in) {
    if (processCount >= 1000) {
        cout << "Maximum number of processes reached!" << endl;
        return;
    }
    in.PID = processCount;
    processList.push_back(in);
    processCount++;
}

int ProcessManager::GetListSize() {
    return processList.size();
}

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
    PID = 0;
    startTime = 0;
    priority = 0;
    processingTime = 0;
    size = 0;
    printer = false;
    scanner = false;
    driver = false;
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
    driver = false;
    disk = 0;
}
