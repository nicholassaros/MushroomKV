#pragma once

#include "TaskQueue.h"
#include "Worker.h"

#include <vector>
#include <thread>
#include <spdlog/spdlog.h>

class WorkerManager {
public:
    WorkerManager(int, std::shared_ptr<TaskQueue>);

    void Start();

    ~WorkerManager();

private:
    int                         m_WorkerCount;
    std::vector<Worker>         m_Workers;
    std::vector<std::jthread>   m_Threads;
};