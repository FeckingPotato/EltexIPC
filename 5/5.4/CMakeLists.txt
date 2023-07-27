cmake_minimum_required(VERSION 3.24)
project(5.4client C)
project(5.4server C)

set(CMAKE_C_STANDARD 23)

add_executable(5.4client client.c)
add_executable(5.4server server.c)
