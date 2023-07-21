cmake_minimum_required(VERSION 3.22)
project(2.1write C)
project(2.1read C)

set(CMAKE_C_STANDARD 23)

add_executable(2.1write write.c)
add_executable(2.1read read.c)
