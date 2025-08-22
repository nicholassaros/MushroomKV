cmake_minimum_required(VERSION 3.10)
project(MushroomKV LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

file(GLOB SERVER_SOURCES src/*.cpp)

add_executable(server ${SERVER_SOURCES})

target_link_libraries(server PRIVATE spdlog::spdlog nlohmann_json::nlohmann_json)
