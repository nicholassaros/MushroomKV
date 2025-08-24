#pragma once

#include <atomic>
#include <spdlog/spdlog.h>

class Session {
public:

    Session(int);

    int getSessionFd();

    int getSessionId();

    bool isAlive();

    void markDead();

    static int generateId();

private:
    int m_SessionFd;
    int m_SessionId;
    std::atomic<bool> m_alive{true};
};