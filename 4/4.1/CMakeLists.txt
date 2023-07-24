cmake_minimum_required(VERSION 3.22)
project(4.1write C)
project(4.1read C)

set(CMAKE_C_STANDARD 23)

add_executable(4.1write write.c semaphore_wrapper.c semaphore_wrapper.h)
add_executable(4.1read read.c semaphore_wrapper.c semaphore_wrapper.h)
