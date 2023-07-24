cmake_minimum_required(VERSION 3.22)
project(4.2 C)

set(CMAKE_C_STANDARD 23)

add_executable(4.2 main.c semaphore_wrapper.c semaphore_wrapper.h)
