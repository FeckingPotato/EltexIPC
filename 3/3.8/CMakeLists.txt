cmake_minimum_required(VERSION 3.22)
project(3.8server C)
project(3.8client C)

set(CMAKE_C_STANDARD 23)

add_executable(3.8server server.c msgStruct.h)
add_executable(3.8client client.c msgStruct.h)
