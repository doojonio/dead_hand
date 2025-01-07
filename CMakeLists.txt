cmake_minimum_required(VERSION 3.28.2)

project(dead_hand LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)

include(cmake/fetch_deps.cmake)
include(cmake/find_deps.cmake)

add_subdirectory(src)

add_executable(
    dead_hand
    ${DH_SRC}
)

target_link_libraries(
    dead_hand
    PUBLIC
        nlohmann_json::nlohmann_json
        cpr::cpr
        CURL::libcurl
        magic_enum::magic_enum
        mailio
        cryptopp
        eventpp
)

target_include_directories(
    dead_hand
    PUBLIC
        ${PROJECT_BINARY_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
