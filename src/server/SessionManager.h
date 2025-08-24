#pragma once

#include "Session.h"

#include <unordered_map>
#include <mutex>
#include <memory>
#include <spdlog/spdlog.h>

class SessionManager {
public:
    
    int addSession(const int);

    void removeSession(const int);

    Session* getSession(const int);

private:
    std::unordered_map<int, std::unique_ptr<Session>> m_SessionMap;
    std::mutex m_MapMutex;
};