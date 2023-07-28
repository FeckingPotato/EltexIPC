cmake_minimum_required(VERSION 3.24)
project(6.3client C)
project(6.3server C)

set(CMAKE_C_STANDARD 23)

add_executable(6.3client client.c)
add_executable(6.3server server.c)
