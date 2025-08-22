#ifndef WORKER_H
#define WORKER_H

#include "DatastoreManager.h"
#include "RequestManager.h"
#include "ResponseBuilder.h"

#include <iostream>
#include <spdlog/spdlog.h>


class Worker {
public:
    Worker();

    void Run(int, std::string);

private:
    void SendResponse(int, DatastoreResult);

    std::string SerializeResult(DatastoreResult);

    DatastoreResult ProcessRequest(std::optional<Request>);

    RequestManager      m_RequestManager;
    DatastoreManager    m_DatastoreManager;
    ResponseBuilder     m_ResponseBuilder;
};


#endif