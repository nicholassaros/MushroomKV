#ifndef DATASTORE_H
#define DATASTORE_H

#include <spdlog/spdlog.h>
#include <unordered_map>

class Datastore {
public:
    Datastore();

    std::optional<std::string> Get(std::string);

    bool Put(std::string, std::string);

    bool Del(std::string);

private:
    std::unordered_map<std::string, std::string> m_DatastoreMap;
};

#endif