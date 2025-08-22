#ifndef WORKER_H
#define WORKER_H

#include "DatastoreManager.h"
#include "RequestManager.h"
#include "ResponseBuilder.h"

#include <iostream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <cstring>      
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <sstream>


class Worker {
public:
    Worker();

    void Run(int, std::string);

private:
    void SendResponse(int, DatastoreResult);

    const char* SerializeResult(DatastoreResult);

    DatastoreResult ProcessRequest(std::optional<Request>);

    RequestManager      m_RequestManager;
    DatastoreManager    m_DatastoreManager;
    ResponseBuilder     m_ResponseBuilder;
};


#endif