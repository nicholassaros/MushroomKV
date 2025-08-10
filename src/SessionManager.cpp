#include "Session.h"
#include "SessionManager.h"

#include <spdlog/spdlog.h>
#include <mutex>

int SessionManager::addSession(const int fd) {
    std::unique_ptr<Session> sessionPtr = std::make_unique<Session>(fd);
    const int sessionId = sessionPtr->getSessionId();

    std::lock_guard<std::mutex> lock(m_MapMutex);
    m_SessionMap[sessionId] = std::move(sessionPtr);
    return sessionId;
};

Session* SessionManager::getSession(const int id) {
    std::lock_guard<std::mutex> lock(m_MapMutex);
    return m_SessionMap[id].get();
};

void SessionManager::removeSession(const int id) {
    spdlog::info("Removing session " + std::to_string(id));
};



