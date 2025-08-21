#include "Worker.h"



Worker::Worker() {

};

DatastoreResult Worker::ProcessRequest(std::optional<Request> rawRequest) {
    if (!rawRequest){
        return "INVALID REQUEST";
    }

    Request request = rawRequest.value();

    switch (request.type) {
        case RequestType::GET:
            return m_DatastoreManager.Get(request.key);

        case RequestType::PUT:
            return m_DatastoreManager.Put(request.key, request.value);

        
    }


    if (request.type == RequestType::GET){
        return m_DatastoreManager.Get(request.key);
    } 
}

void Worker::Run(int client_fd, std::string data) {

    // parse data into request
    std::optional<Request> rawRequest = m_RequestManager.HandleRequest(data);

    DatastoreResult result = ProcessRequest(rawRequest);




    if (!rawRequest){
        SendResponse(client_fd, "INVALID REQUEST");
    }

    // route request to DataManager
    Request request = rawRequest.value();

    if (request.type == RequestType::GET){

    }

    // get result form DataManager

    // send result back to client
};



