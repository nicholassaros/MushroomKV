#include <spdlog/spdlog.h>
#include <iostream>

#include "SessionManager.h"

int main(){
    spdlog::info("Welcome to spdlog!");
    spdlog::warn("This is a warning!");
    spdlog::error("This is an error with a number: {}", 42);

    SessionManager sessionManager;

    sessionManager.removeSession(111);

    return 1;
}