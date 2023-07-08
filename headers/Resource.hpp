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

public:
    ResourceManager();
    static ResourceManager* GetInstance();
};

#endif
