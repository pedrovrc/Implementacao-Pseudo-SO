#include "headers/File.hpp"

FileManager& FileManager::GetInstance() {
    static FileManager manager;
    return manager;
}