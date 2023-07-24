cmake_minimum_required(VERSION 3.22)
project(4.4write C)
project(4.4read C)

set(CMAKE_C_STANDARD 23)

add_executable(4.4write write.c semaphore_wrapper.c semaphore_wrapper.h)
add_executable(4.4read read.c semaphore_wrapper.c semaphore_wrapper.h)
