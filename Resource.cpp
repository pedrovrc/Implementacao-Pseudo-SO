#include "headers/Resource.hpp"

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
