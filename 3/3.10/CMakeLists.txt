cmake_minimum_required(VERSION 3.22)
project(3.10write C)
project(3.10read C)

set(CMAKE_C_STANDARD 23)

add_executable(3.10write write.c msgStruct.h posixPort.h posixPort.c)
add_executable(3.10read read.c msgStruct.h posixPort.h posixPort.c)
