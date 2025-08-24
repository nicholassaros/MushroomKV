#pragma once

#include "DatastoreManager.h"

#include <iostream>
#include <spdlog/spdlog.h>

class RequestManager {
public:
    RequestManager();

    std::optional<Request> HandleRequest(std::string);

private:
};