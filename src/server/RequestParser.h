#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <iostream>
#include <optional>
#include <spdlog/spdlog.h>


enum class RequestType {
    GET,
    PUT 
};

struct Request {
    RequestType type;
    std::string key;
    std::string value;

    Request(RequestType type, std::string key, std::string value)
        : type(type), key(key), value(value) {
    };

};

class RequestParser {
public:
    static std::optional<Request> parse(const std::string& input);
};

#endif