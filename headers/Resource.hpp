#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <bits/stdc++.h>
using namespace std;

/*
    Class ResourceManager

    Classe que representa o Gerenciador de Recursos (dispositivos de E/S) do Pseudo-SO.
    Essa classe segue o padrão singleton.
*/
class ResourceManager {
    static ResourceManager* instance;
    vector<int> scannerQueue;
    vector<int> printerQueue1;
    vector<int> printerQueue2;
    vector<int> modemQueue;
    vector<int> SATAQueue1;
    vector<int> SATAQueue2;

public:
    ResourceManager();
    static ResourceManager* GetInstance();
    void IORequest();
};

#endif
