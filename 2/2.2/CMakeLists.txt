cmake_minimum_required(VERSION 3.22)
project(2.2write C)
project(2.2read C)

set(CMAKE_C_STANDARD 23)

add_executable(2.2write write.c)
add_executable(2.2read read.c)
