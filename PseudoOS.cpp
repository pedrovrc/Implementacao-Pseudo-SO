#include "headers/PseudoOS.hpp"

PseudoOS::PseudoOS() {
    fileManager = fileManager.GetInstance();
    memoryManager = memoryManager.GetInstance();
    processManager = processManager.GetInstance();
    queueManager = queueManager.GetInstance();
    resourceManager = resourceManager.GetInstance();
}

PseudoOS& PseudoOS::GetInstance() {
    static PseudoOS system;
    return system;
}

bool PseudoOS::Run (fstream* file1, fstream* file2) {
    bool result = false;
    
    // le arquivo 1
    // armazena detalhes dos processos
    result = ReadProcessInput(file1);
    if (result) {
        processManager.PrintList(); // debug
        cout << "Arquivo de processos lido com sucesso" << endl;
    } else {
        cout << "Erro ao ler arquivo de processos" << endl;
        return false;
    }

    // le arquivo 2
    // atualiza estado do sistema de arquivos
    result = ReadFileSystemInput(file2);
    if (result) {
        cout << "Arquivo de sistema de arquivos lido com sucesso" << endl;
    } else {
        cout << "Erro ao ler arquivo de sistema de arquivos" << endl;
        return false;
    }
    
    // cria dispatcher

    // executa lista de processos em ordem
    
    // imprimir historico das operacoes do sistema de arquivos
    // imprimir mapa atual de ocupacao do disco
    
    return true;
}

bool PseudoOS::ReadProcessInput(fstream* file) {
    string line;
    string buffer;
    Process holder;
    int i = 0, value, value_counter = 0;

    if(file->is_open() == false) return false;

    // leitura do arquivo de entrada linha a linha
    while(!file->eof()) {
        getline(*file, line);

        i = 0;
        holder.Reset();
        value_counter = 0;
        while(i < line.size()) {

            // salva numero em buffer ate encontrar virgula
            buffer = "";
            do {
                buffer += line[i];
                i++;
            } while (i < line.size() && line[i] != ',');
            i += 2;    // pula espaco apos virgula

            // salva valor encontrado no campo correto do processo
            value = atoi(buffer.c_str());
            if (value_counter == 0) holder.startTime = value;
            else if (value_counter == 1) holder.priority = value;
            else if (value_counter == 2) holder.processingTime = value;
            else if (value_counter == 3) holder.size = value;
            else if (value_counter == 4) holder.printer = (bool)value;
            else if (value_counter == 5) holder.scanner = (bool)value;
            else if (value_counter == 6) holder.driver = (bool)value;
            else if (value_counter == 7) holder.disk = value;

            value_counter++;
        }

        // adiciona processo a lista
        processManager.AddProcess(holder);
    }
    return true;
}

bool PseudoOS::ReadFileSystemInput(fstream* file) {
    return true;
}
