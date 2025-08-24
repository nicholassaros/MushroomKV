#pragma once

#include "DatastoreManager.h"
#include "RequestManager.h"
#include "ResponseBuilder.h"
#include "DatastoreResult.h"
#include "TaskQueue.h"

#include <iostream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <cstring>      
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <stop_token>
#include <thread>


class Worker {
public:
    Worker(int, std::shared_ptr<TaskQueue>);

    void operator()(std::stop_token st);

private:
    void SendResponse(int, DatastoreResult);

    std::string ReadClientData(int);

    const char* SerializeResult(DatastoreResult);

    DatastoreResult ProcessRequest(std::optional<Request>);

    int                         m_Id;
    std::shared_ptr<TaskQueue>  m_TaskQueue;
    RequestManager              m_RequestManager;
    DatastoreManager            m_DatastoreManager;
    ResponseBuilder             m_ResponseBuilder;
};