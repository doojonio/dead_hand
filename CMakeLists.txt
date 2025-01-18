cmake_minimum_required(VERSION 3.28.2)

project(dead_hand LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)

include(cmake/fetch_deps.cmake)
include(cmake/find_deps.cmake)

add_subdirectory(src)

add_executable(
    ${PROJECT_NAME}
    ${DH_SRC}
)

enable_testing()
add_subdirectory(test)


target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        nlohmann_json::nlohmann_json
        cpr::cpr
        CURL::libcurl
        magic_enum::magic_enum
        mailio
        cryptopp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${PROJECT_BINARY_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
