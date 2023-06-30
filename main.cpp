#include <bits/stdc++.h>
using namespace std;

#include "headers/PseudoOS.hpp"

void main(int argc, char *argv[]) {
    if (argc <= 2) {
        cout << "Erro! Insira os arquivos via linha de comando." << endl;
        return;
    }

    // abre arquivos
    string filenameA = argv[1];
    ofstream* fileA = new ofstream();
    fileA->open(filenameA);

    string filenameB = argv[2];
    ofstream* fileB = new ofstream();
    fileB->open(filenameB);

    // executa sistema passando arquivos
    bool r;
    PseudoOS& system = system.GetInstance();
    r = system.Run(fileA, fileB);

    // reporta execucao
    if (r) {
        cout << "Sistema executado com sucesso." << endl;
    } else {
        cout << "Sistema executou com erros." << endl;
    }

    return;
}
