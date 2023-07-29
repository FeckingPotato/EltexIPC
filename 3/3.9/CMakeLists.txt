cmake_minimum_required(VERSION 3.22)
project(3.9server C)
project(3.9client C)

set(CMAKE_C_STANDARD 23)

add_executable(3.9server server.c msgStruct.h)
add_executable(3.9client client.c msgStruct.h)
