#include "Session.h"
#include "SessionManager.h"

#include <spdlog/spdlog.h>
#include <mutex>

int SessionManager::addSession(const int fd) {
    pdlog::info("Adding session with FD: " + std::to_string(fd));
    std::unique_ptr<Session> sessionPtr = std::make_unique<Session>(fd);

    std::lock_guard<std::mutex> lock(m_MapMutex);
    m_SessionMap[fd] = std::move(sessionPtr);
    return fd;
};

Session* SessionManager::getSession(const int fd) {
    spdlog::info("Retrieving session with id: " + std::to_string(fd));
    std::lock_guard<std::mutex> lock(m_MapMutex);

    if(m_SessionMap.find(fd) == m_SessionMap.end()) {
        return nullptr;
    }

    return m_SessionMap[fd].get();
};

void SessionManager::removeSession(const int fd) {
    spdlog::info("Removing session with id: " + std::to_string(fd));
    std::lock_guard<std::mutex> lock(m_MapMutex);
    m_SessionMap.erase(fd);
};



