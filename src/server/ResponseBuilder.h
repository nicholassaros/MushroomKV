#pragma once

#include "RequestParser.h"

#include <iostream>
#include <spdlog/spdlog.h>

struct Response {
    RequestType requestType;
    std::string data;

    Response(RequestType, std::string);
};

class ResponseBuilder {
public:
    static Response build(RequestType, std::string);
};