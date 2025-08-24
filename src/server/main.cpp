#include "Server.h"
#include "TaskQueue.h"
#include "WorkerManager.h"


#include <spdlog/spdlog.h>


int main() {

    std::shared_ptr<TaskQueue> taskQueue = std::make_shared<TaskQueue()>

    WorkerManager workerManager = 


    Server myServer = Server(8000, taskQueue);



    myServer.Start();
    return 0;
}