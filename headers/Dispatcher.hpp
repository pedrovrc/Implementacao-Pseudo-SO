#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <bits/stdc++.h>
using namespace std;

#include "Process.hpp"
#include "File.hpp"

/*
    Class Dispatcher

    Classe que implementa o processo Dispatcher do Pseudo-SO.
    É responsável por:
        - Imprimir no terminal uma mensagem detalhando os atributos de um processo quando ele for executado;
        - Imprimir no terminal uma mensagem detalhando o histórico de operações feitas no sistema de arquivos (após execução do sistema);
        - Imprimir no terminal uma representação do estado atual do disco e seus blocos (após execução do sistema).
    Essa classe segue o padrão singleton.
*/
class Dispatcher {
    static Dispatcher* instance;

public:
    Dispatcher();
    static Dispatcher* GetInstance();
    void PrintProcess(Process& proc);
    void PrintOperationHistory();
    void PrintFileSystemState();
};

#endif