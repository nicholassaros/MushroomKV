cmake_minimum_required(VERSION 3.10)
project(MushroomKV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)

file(GLOB SERVER_SOURCES src/server/*.cpp)
file(GLOB CLIENT_SOURCES src/client/*.cpp)

add_executable(server ${SERVER_SOURCES})

add_executable(client ${CLIENT_SOURCES})

target_link_libraries(server PRIVATE spdlog::spdlog)
target_link_libraries(client PRIVATE spdlog::spdlog)
