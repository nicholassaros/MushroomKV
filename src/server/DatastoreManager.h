#ifndef DATASTORE_MANAGER_H
#define DATASTORE_MANAGER_H

#include "Datastore.h"
#include "DatastoreResult.h"
#include "RequestParser.h"


#include <iostream>
#include <spdlog/spdlog.h>

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