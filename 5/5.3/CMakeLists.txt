cmake_minimum_required(VERSION 3.24)
project(5.3client C)
project(5.3server C)

set(CMAKE_C_STANDARD 23)

add_executable(5.3client client.c)
add_executable(5.3server server.c)
