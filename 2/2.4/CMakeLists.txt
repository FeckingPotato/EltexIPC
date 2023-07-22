cmake_minimum_required(VERSION 3.22)
project(2.4write C)
project(2.4read C)

set(CMAKE_C_STANDARD 23)

add_executable(2.4write write.c)
add_executable(2.4read read.c)
