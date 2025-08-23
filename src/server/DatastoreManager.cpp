#include "DatastoreManager.h"
#include "Datastore.h"

DatastoreManager::DatastoreManager()
    : m_Datastore(Datastore()) {

};

DatastoreResult DatastoreManager::BuildResult(StatusCode status, std::optional<std::string> data) {
    switch (status) {
        case (StatusCode::OK):
            return DatastoreResult(StatusCode::OK, "SUCCESS", data);
        case (StatusCode::ERROR):
            return DatastoreResult(StatusCode::ERROR, "ERROR", data);
    }
    return DatastoreResult(StatusCode::ERROR, "ERROR", data); 
}

DatastoreResult DatastoreManager::Get(std::string key) {
    std::optional<std::string> data = m_Datastore.Get(key);

    if (!data) {
        spdlog::info("Key {} was not found in the datastore", key);
        return BuildResult(StatusCode::ERROR,data);
    }
    spdlog::info("Key {} found in the datastore", key);
    return BuildResult(StatusCode::OK, data);
};

DatastoreResult DatastoreManager::Put(std::string key, std::string value) {
    if (m_Datastore.Put(key, value)){
        return BuildResult(StatusCode::OK, std::nullopt);
    }
    return BuildResult(StatusCode::ERROR, std::nullopt);
};

DatastoreResult DatastoreManager::Del(std::string key) {
    if (m_Datastore.Del(key)){
        return BuildResult(StatusCode::OK, std::nullopt);
    }
    return BuildResult(StatusCode::ERROR, std::nullopt);
};
