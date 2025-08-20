#include "RequestParser.h"

#include <iostream>
#include <optional>
#include <sstream>


std::optional<Request> RequestParser::parse(const std::string& input) {

    std::istringstream stringStream(input);
    std::string command, key, value;

    stringStream >> command >> key >> value;

    if (command == "GET" && !key.empty()){
        return Request(RequestType::GET, key, "");
    } else if (command == "PUT" && !key.empty() && !value.empty()) {
        return Request(RequestType::PUT, key, value);
    }
    return std::nullopt;
}
