#include "Server.h"
#include "TaskQueue.h"
#include "WorkerManager.h"


#include <spdlog/spdlog.h>


int main() {

    std::shared_ptr<TaskQueue> taskQueue = std::make_shared<TaskQueue>();

    WorkerManager workerManager = WorkerManager(5, taskQueue);
    workerManager.Start();

    Server myServer = Server(8080, taskQueue);
    myServer.Start();
    return 0;
}