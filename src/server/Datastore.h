#ifndef DATASTORE_H
#define DATASTORE_H

#include <spdlog/spdlog.h>

class Datastore {
public:
    Datastore();

    std::optional<std::string> GET(std::string);

    bool PUT(std::string, std::string);

    bool DEL(std::string);

private:
};

#endif