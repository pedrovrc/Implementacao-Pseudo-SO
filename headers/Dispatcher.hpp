#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <bits/stdc++.h>
using namespace std;

#include "Process.hpp"

class Dispatcher {

public:
    static Dispatcher& GetInstance();
    void PrintProcess(Process& proc);
};

#endif