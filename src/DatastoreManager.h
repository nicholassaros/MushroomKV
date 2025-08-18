#ifndef DATASTORE_MANAGER_H
#define DATASTORE_MANAGER_H

#include "Datastore.h"
#include "RequestParser.h"

#include <iostream>

class DatastoreManager {
public:

    DatastoreManager();

    void executeRequest(Request);

    std::string get(std::string key);

    bool put(std::string key, std::string value);

    bool del(std::string key);
private:
    Datastore m_Datastore;
};

#endif