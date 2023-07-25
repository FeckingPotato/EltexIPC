cmake_minimum_required(VERSION 3.22)
project(4.8 C)

set(CMAKE_C_STANDARD 23)

add_executable(4.8 main.c shmem_wrapper.h shmem_wrapper.c)
