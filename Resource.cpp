#include "headers/Resource.hpp"

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager manager;
    return manager;
}