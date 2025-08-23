#include "Worker.h"

using json = nlohmann::json;


Worker::Worker() {

};

const char* Worker::SerializeResult(DatastoreResult result) {
    json jsonResult;

    jsonResult["status"] = result.status;
    jsonResult["data"] = "";
    jsonResult["message"] = result.message;
    
    if (!result.data) {
        jsonResult["data"] = result.data.value();
    }
    return jsonResult.dump().c_str();
}

void Worker::SendResponse(int client_fd, DatastoreResult result) {
    const char* serializedResult = SerializeResult(result);

    ssize_t bytes_sent = send(client_fd, serializedResult, strlen(serializedResult), 0);
    if (bytes_sent == -1) {
        spdlog::error("Result was not successfully sent to client {}", client_fd);
        return;
    }
    spdlog::info("Successfully sent result to client {}", client_fd);
}

DatastoreResult Worker::ProcessRequest(std::optional<Request> rawRequest) {
    if (!rawRequest){
        return DatastoreResult(StatusCode::INVALID, "INVALID REQUEST", "");
    }

    Request request = rawRequest.value();

    switch (request.type) {
        case RequestType::GET:
            return m_DatastoreManager.Get(request.key);

        case RequestType::PUT:
            return m_DatastoreManager.Put(request.key, request.value);
        
        case RequestType::DELETE:
            return m_DatastoreManager.Del(request.key);
    }
}

void Worker::Run(int client_fd, std::string data) {

    // parse data into request
    std::optional<Request> rawRequest = m_RequestManager.HandleRequest(data);

    DatastoreResult result = ProcessRequest(rawRequest);

    SendResponse(client_fd, result);
};



