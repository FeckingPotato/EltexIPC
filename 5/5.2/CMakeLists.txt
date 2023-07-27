cmake_minimum_required(VERSION 3.24)
project(5.2client C)
project(5.2server C)

set(CMAKE_C_STANDARD 23)

add_executable(5.2client client.c)
add_executable(5.2server server.c)
