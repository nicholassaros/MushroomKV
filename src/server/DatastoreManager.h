#ifndef DATASTORE_MANAGER_H
#define DATASTORE_MANAGER_H

#include "Datastore.h"
#include "RequestParser.h"

#include <iostream>
#include <spdlog/spdlog.h>

enum class StatusCode {
    OK,
    ERROR,
    INVALID
};

struct DatastoreResult {
    StatusCode status;
    std::string message;
    std::optional<std::string> data;
};

class DatastoreManager {
public:

    DatastoreManager();

    void executeRequest(Request);

    DatastoreResult Get(std::string key);

    DatastoreResult Put(std::string key, std::string value);

    DatastoreResult Del(std::string key);
private:
    Datastore m_Datastore;

    DatastoreResult BuildResult(StatusCode status, std::optional<std::string>);
};

#endif