#include "DatastoreManager.h"
#include "Datastore.h"

DatastoreManager::DatastoreManager()
    : m_Datastore(Datastore()) {

};

std::string DatastoreManager::get(std::string key) {
    return "";
};

bool DatastoreManager::put(std::string key, std::string value) {
    return true;
};

bool DatastoreManager::del(std::string key) {
    return false;
};
