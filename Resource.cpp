#include "headers/Resource.hpp"
#include "headers/Process.hpp"

// ----------------------------------------------------
// Essa região do código implementa o padrão singleton.

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager() {
    if (instance != nullptr) return;
    instance = this;
}

ResourceManager* ResourceManager::GetInstance() {
    if (instance == nullptr) {
		instance = new ResourceManager();
	}
		return instance;
}
// ----------------------------------------------------


// organiza as solicitações de E/S por fila de processo
void ResourceManager::IORequest(){
    vector<Process> processList = ProcessManager::GetInstance()->processList;
    for(int i = 0; i < processList.size(); i++){
        if(processList[i].printer == 1){
            printerQueue1.push_back(processList[i].PID);
        }else if(processList[i].printer == 2){
            printerQueue2.push_back(processList[i].PID);
        }
        if(processList[i].scanner) scannerQueue.push_back(processList[i].PID);
        if(processList[i].modem) modemQueue.push_back(processList[i].PID);
        if(processList[i].SATA == 1){
            SATAQueue1.push_back(processList[i].PID);
        }else if(processList[i].SATA == 2){
            SATAQueue2.push_back(processList[i].PID);
        }
    }
 }
  
