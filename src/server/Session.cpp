#include "Session.h"

#include <random>

Session::Session(int fd) :
    m_SessionFd(fd), m_SessionId(Session::generateId()){

};

int Session::getSessionFd() {
    return m_SessionFd;
};

int Session::getSessionId() {
    return m_SessionId;
};

int Session::generateId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(100000, 999999);
    return distrib(gen);
};