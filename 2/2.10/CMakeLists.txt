cmake_minimum_required(VERSION 3.22)
project(2.10write C)
project(2.10read C)

set(CMAKE_C_STANDARD 23)

add_executable(2.10write write.c)
add_executable(2.10read read.c)
