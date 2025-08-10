cmake_minimum_required(VERSION 3.10)
project(MushroomKV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/spdlog)

add_executable(server
    src/server.cpp
    src/SessionManager.cpp
    src/Session.cpp
)

add_executable(client src/client.cpp)

target_link_libraries(server PRIVATE spdlog::spdlog)
target_link_libraries(client PRIVATE spdlog::spdlog)
