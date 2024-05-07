cmake_minimum_required(VERSION 3.28)
project(socket_server)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ./include
)

file(GLOB_RECURSE SOURCES
    "./source/*.*"
)

add_executable(socket_server main.cpp ${SOURCES})
