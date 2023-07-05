#include "headers/Process.hpp"

ProcessManager& ProcessManager::GetInstance() {
    static ProcessManager manager;
    return manager;
}

Process::Process() {
    PID = 0;
    priority = 0;
    memoffset = 0;
    size = 0;
    printer = false;
    scanner = false;
    driver = false;
}

Process::Process( int ID,
                  int CPUpriority,
                  int offset,
                  int block_size,
                  bool print_use,
                  bool scanner_use,
                  bool driver_use) {
    PID = ID;
    priority = CPUpriority;
    memoffset = offset;
    size = block_size;
    printer = print_use;
    scanner = scanner_use;
    driver = driver_use;
}