#ifndef DATASTORE_RESULT
#define DATASTORE_RESULT

#include <iostream>
#include <optional>

enum class StatusCode {
    OK,
    ERROR,
    INVALID
};

struct DatastoreResult {
    StatusCode status;
    std::string message;
    std::optional<std::string> data;

    DatastoreResult(StatusCode status, std::string message, std::optional<std::string> data)
        : status(status), message(message), data(data) {
            
        }
};
#endif