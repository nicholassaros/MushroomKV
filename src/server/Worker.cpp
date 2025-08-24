#include "Worker.h"

using json = nlohmann::json;


Worker::Worker(int id, std::shared_ptr<TaskQueue> taskQueue)
    :   m_Id(id),
        m_TaskQueue(taskQueue) {
};

void Worker::operator()(std::stop_token st) {
    while (!st.stop_requested()) {
        spdlog::info("Worker {} waiting on new task");

        Task task = m_TaskQueue->Pop();
        spdlog::info("Worker {} processing new task", m_Id); 

        std::string rawData = ReadClientData(task.client_fd);

        std::optional<Request> request = m_RequestManager.HandleRequest(rawData);

        DatastoreResult result = ProcessRequest(request);
        spdlog::info("Worker {} returned result with status {}", m_Id, result.message); 

        SendResponse(task.client_fd, result);
        spdlog::info("Worker {} sent response to client {}", m_Id, task.client_fd); 
    }
}

std::string Worker::ReadClientData(int client_fd) {
    char buffer[1024];
    std::string data;

    spdlog::info("Worker {} reading from client {}", m_Id, client_fd); 
    while (true) {
        int bytes_read = read(client_fd, buffer, sizeof(buffer));
        if (bytes_read > 0) {

            data.append(buffer, bytes_read);

        } else if (bytes_read == 0) {
            // Client disconnected
            spdlog::info("Client disconnected"); 
            close(client_fd);
            break;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // No more data available to read (expected with EPOLLET)
                break;
            } else {
                // Read error
                spdlog::error("Error reading from client socket"); 
                close(client_fd);
                break;
            }
        }
    }
    return data;
}

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
    return DatastoreResult(StatusCode::INVALID, "INVALID REQUEST", "");
}

