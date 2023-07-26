cmake_minimum_required(VERSION 3.24)
project(5.1client C)
project(5.1server C)

set(CMAKE_C_STANDARD 23)

add_executable(5.1client client.c)
add_executable(5.1server server.c)
