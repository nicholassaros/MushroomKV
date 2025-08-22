#include "Datastore.h"


Datastore::Datastore(){

};

std::optional<std::string> Datastore::Get(std::string key) {
    if (m_DatastoreMap.find(key) != m_DatastoreMap.end()){
        return m_DatastoreMap[key];
    }
    return std::nullopt;
}

bool Datastore::Put(std::string key, std::string value) {
    m_DatastoreMap[key] = value;
    return true;
}

bool Datastore::Del(std::string key) {
    m_DatastoreMap.erase(key);
    return true;
}