#include "headers/Queue.hpp"

QueueManager& QueueManager::GetInstance() {
    static QueueManager manager;
    return manager;
}