#include "RequestManager.h"

RequestManager::RequestManager() {

};

std::optional<Request> RequestManager::HandleRequest(std::string data){
    spdlog::info("RequestManager recieved raw data: {}", data);
    std::optional<Request> request = RequestParser::parse(data);

    return request;
};
