#include "WorkerManager.h"


WorkerManager::WorkerManager(int workerCount, std::shared_ptr<TaskQueue> taskQueue)
    :   m_WorkerCount(workerCount) {

    for(int i = 0; i<m_WorkerCount; i++) {
        spdlog::info("Creating worker with ID: {}",i);
        m_Workers.emplace_back(Worker(i, taskQueue));
    }
};

WorkerManager::~WorkerManager() {
    spdlog::info("Worker Manager shutting down");
};

void WorkerManager::Start() {
    for(auto& worker : m_Workers) {
        m_Threads.emplace_back(std::ref(worker));
    }
}