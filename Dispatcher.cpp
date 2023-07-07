#include "Dispatcher.hpp"
#include "Memory.hpp"

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
