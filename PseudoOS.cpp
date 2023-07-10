#include "headers/PseudoOS.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

PseudoOS* PseudoOS::instance;

PseudoOS::PseudoOS() {
    if (instance != nullptr) return;
    instance = this;
    fileManager = FileManager::GetInstance();
    memoryManager = MemoryManager::GetInstance();
    processManager = ProcessManager::GetInstance();
    queueManager = QueueManager::GetInstance();
    resourceManager = ResourceManager::GetInstance();
    currentProcessID = -1;
}

PseudoOS& PseudoOS::GetInstance() {
    if (instance == nullptr) {
		instance = new PseudoOS();
	}
		return *instance;
}
// ----------------------------------------------------

/*
    bool PseudoOS::Run (fstream* file1, fstream* file2)

    Método principal da execução do Pseudo-SO.
        - Lê e armazena de dados de entrada;
        - Cria processo Dispatcher;
        - Executa loop de criação e execução de processos;
            - A cada instrucao executada, se o processo tiver alguma
            operacao de sistema de arquivos para fazer, a executa.
        - Imprime mensagens finais do Dispatcher ao final da execução.
*/
bool PseudoOS::Run (fstream* file1, fstream* file2) {
    bool result = false;
    
    // le arquivo 1
    // armazena detalhes dos processos
    result = ReadProcessInput(file1);
    if (result) {
        // processManager->PrintList(); // debug
        cout << "Arquivo de processos lido com sucesso" << endl;
    } else {
        cout << "Erro ao ler arquivo de processos" << endl;
        return false;
    }

    // le arquivo 2
    // atualiza estado do sistema de arquivos
    result = ReadFileSystemInput(file2);
    if (result) {
        // fileManager->PrintFiles();   // debug
        // fileManager->PrintOperations();  // debug
        cout << "Arquivo de sistema de arquivos lido com sucesso" << endl;
    } else {
        cout << "Erro ao ler arquivo de sistema de arquivos" << endl;
        return false;
    }
    cout << endl;
    
    // cria dispatcher
    Dispatcher* dispatcher = dispatcher->GetInstance();

    int quantumCount = 0, offset;
    Process* currentProcess = nullptr;

    // enquanto houver processos a serem executados/criados ou CPU estiver ocupada
    while (queueManager->creationQueue.empty() == false || currentProcessID != -1) {
        //cout << "quantum counter: " << quantumCount << endl << endl;

        // para cada processo na lista de processos de entrada
        for (int i = 0; i < queueManager->creationQueue.size(); i++) {   
            // checa se há processo para entrar nesse momento
            if (queueManager->creationQueue[i]->startTime == quantumCount) {
                // processo entra na fila de execucao e sai da de criacao
                queueManager->AddProcessExecution(queueManager->creationQueue[i]);
                queueManager->creationQueue.erase(queueManager->creationQueue.begin() + i);
                i--;
            }
        }

        // se houver processos em fila de execucao
        if (queueManager->realTimeQueue.empty() == false ||
            queueManager->userQueue.empty() == false) {

            // pega processo prioritario
            if (queueManager->realTimeQueue.empty() == false) {
                currentProcess = queueManager->realTimeQueue[0]; // FIFO
            } else {
                currentProcess = queueManager->GetUserProcess();
            } 

            offset = memoryManager->GetOffset(currentProcess->PID);
            // se nao estiver em memoria
            if (offset == -1) offset = memoryManager->FindSpace(*currentProcess);
            if (offset != -1) {
                memoryManager->Allocate(*currentProcess, offset);
                // se CPU estiver vaga
                if (currentProcessID == -1) {
                    // processo toma posse da CPU
                    currentProcessID = currentProcess->PID;
                    queueManager->RemoveFromExecQueue(currentProcess->PID, currentProcess->priority);
                    dispatcher->PrintProcess(*currentProcess);
                }
            }
        }

        // se CPU estiver ocupada por processo
        if (currentProcessID != -1) {
            // executa instrucao do processo
            currentProcess = &processManager->processList[currentProcessID];
            currentProcess->ExecuteInstruction();

            // se processo executou instrucao final
            if (currentProcess->instructionCount > currentProcess->processingTime){
                // libera memória ocupada por processo
                offset = memoryManager->GetOffset(currentProcess->PID);
                memoryManager->Free(currentProcess->size, offset);

                // retira processo da CPU
                currentProcessID = -1;
                currentProcess = nullptr;
                
            }
        }
 
        // implementar delay?
        quantumCount++;
    }
    
    // imprimir historico das operacoes do sistema de arquivos
    dispatcher->PrintOperationHistory();

    // imprimir mapa atual de ocupacao do disco
    dispatcher->PrintFileSystemState();

    return true;
}

/*
    bool PseudoOS::ReadProcessInput(fstream* file)

    Lê e armazena os dados do primeiro arquivo de entrada (arquivo de processos).
*/
bool PseudoOS::ReadProcessInput(fstream* file) {
    if(file->is_open() == false) return false;
    
    string line;
    string buffer;
    Process holder;
    int i = 0, value, value_counter = 0;

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
            else if (value_counter == 4) holder.printer = value;
            else if (value_counter == 5) holder.scanner = value;
            else if (value_counter == 6) holder.modem = value;
            else if (value_counter == 4) holder.printer = value;
            else if (value_counter == 5) holder.scanner = value;
            else if (value_counter == 6) holder.modem = value;
            else if (value_counter == 7) holder.SATA = value;

            value_counter++;
        }

        // adiciona processo a lista
        processManager->AddProcess(holder);
    }

    // adiciona processos a fila de criacao
    for (int i = 0; i < processManager->processList.size(); i++) {
        queueManager->AddProcessCreation(&processManager->processList[i]);
    }

    return true;
}

/*
    bool PseudoOS::ReadFileSystemInput(fstream* file)
    
    Lê e armazena os dados do segundo arquivos de entrada (arquivo de sistema de arquivos).
*/
bool PseudoOS::ReadFileSystemInput(fstream* file) {

    if(file->is_open() == false) return false;

    string line;
    string buffer;

    // armazena quantidade de blocos do disco
    getline(*file, line);
    fileManager->diskSize = atoi(line.c_str());
    for (int i = 0; i < fileManager->diskSize; i++) {
        fileManager->occupationMap.push_back('0');
    }

    // armazena quantidade de segmentos ocupados
    getline(*file, line);
    fileManager->occupiedSegments = atoi(line.c_str());

    int i, value_counter;
    File holder;

    // le informacoes de cada arquivo
    for (int j = 0; j < fileManager->occupiedSegments; j++) {
        getline(*file, line);
        i = 0;
        value_counter = 0;

        while(i < line.size()) {
            // salva numero em buffer ate encontrar virgula
            buffer = "";
            do {
                buffer += line[i];
                i++;
            } while (i < line.size() && line[i] != ',');
            i += 2;    // pula espaco apos virgula

            if (value_counter == 0) holder.name = buffer;
            else if (value_counter == 1) holder.offset = atoi(buffer.c_str());
            else if (value_counter == 2) holder.size = atoi(buffer.c_str());

            value_counter++;
        }

        fileManager->AddFile(holder);

        // preenche o occupationMap
        for (int k = holder.offset; k < holder.offset + holder.size; k++) {
            fileManager->occupationMap[k] = holder.name[0];
        }
    }

    FSOperation opholder;

    // le informacoes de cada operacao
    while(!file->eof()) {
        getline(*file, line);
        i = 0;
        value_counter = 0;

        while(i < line.size()) {
            // salva numero em buffer ate encontrar virgula
            buffer = "";
            do {
                buffer += line[i];
                i++;
            } while (i < line.size() && line[i] != ',');
            i += 2;    // pula espaco apos virgula

            if (value_counter == 0) opholder.PID = atoi(buffer.c_str());
            else if (value_counter == 1) opholder.opcode = atoi(buffer.c_str());
            else if (value_counter == 2) opholder.filename = buffer;
            else if (value_counter == 3) opholder.filesize = atoi(buffer.c_str());

            value_counter++;
        }

        fileManager->AddOperation(opholder);
    }

    return true;
}
