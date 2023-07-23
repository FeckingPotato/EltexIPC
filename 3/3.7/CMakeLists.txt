cmake_minimum_required(VERSION 3.22)
project(3.7write C)
project(3.7read C)

set(CMAKE_C_STANDARD 23)

add_executable(3.7write write.c msgStruct.h)
add_executable(3.7read read.c msgStruct.h)
