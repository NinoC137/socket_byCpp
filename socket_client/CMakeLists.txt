cmake_minimum_required(VERSION 3.28)
project(socket_client)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_C_COMPILER arm-none-eabi-gcc)
#set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

file(GLOB_RECURSE SOURCES
        "source/*.*"
)

include_directories(
        includes
)

add_executable(socket_client main.cpp ${SOURCES})