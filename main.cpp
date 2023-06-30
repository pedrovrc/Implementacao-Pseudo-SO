#include <bits/stdc++.h>
using namespace std;

#include "headers/PseudoOS.hpp"

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        cout << "Erro! Insira os arquivos via linha de comando." << endl;
        return 0;
    }

    // abre arquivos
    string filenameA = argv[1];
    fstream* fileA = new fstream();
    fileA->open(filenameA.c_str());

    string filenameB = argv[2];
    fstream* fileB = new fstream();
    fileB->open(filenameB.c_str());

    if (!(fileA->is_open()) && !(fileB->is_open())) {
        cout << "Erro ao abrir arquivos!" << endl;
        return 0;
    }

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

    fileA->close();
    fileB->close();

    return 0;
}
