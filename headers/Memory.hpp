#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <bits/stdc++.h>
using namespace std;

class MemoryManager {

public:
    static MemoryManager& GetInstance();
    int GetOffset(int PID);
};

#endif
