#include "Dispatcher.hpp"
#include "Memory.hpp"
#include "File.hpp"

Dispatcher& Dispatcher::GetInstance() {
    static Dispatcher process;
    return process;
}

void Dispatcher::PrintProcess(Process& proc) {
    cout << "dispatcher =>" << endl;
    cout << "\tPID: " << proc.PID << endl;
    cout << "\toffset: " << MemoryManager::GetInstance().GetOffset(proc.PID) << endl;
    cout << "\tblocks: " << proc.size << endl;
    cout << "\tpriority: " << proc.priority << endl;
    cout << "\ttime: " << proc.processingTime << endl;
    cout << "\tprinters: " << proc.printer << endl;
    cout << "\tscanners: " << proc.scanner << endl;
    cout << "\tmodems: " << proc.modem << endl;
    cout << "\tdrives: " << proc.disk << endl;
    cout << endl;
}

void Dispatcher::PrintOperationHistory() {
    cout << "File System =>" << endl;

    FileManager fileManager = fileManager.GetInstance();

    for (int i = 0; i < fileManager.operationList.size(); i++) {
        if (fileManager.operationList[i].success) {
            cout << "Operation " << i << " => Success" << endl;
        } else {
            cout << "Operation " << i << " => Failed" << endl;
        }

        cout << fileManager.operationList[i].reason << endl;
    }
    cout << endl;
}

void Dispatcher::PrintFileSystemState() {

}
