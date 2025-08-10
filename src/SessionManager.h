#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "Session.h"

#include <unordered_map>
#include <mutex>
#include <memory>

class SessionManager {
public:
    
    int addSession(const int);

    void removeSession(const int);

    Session* getSession(const int);

private:
    std::unordered_map<int, std::unique_ptr<Session>> m_SessionMap;
    std::mutex m_MapMutex;
};

#endif