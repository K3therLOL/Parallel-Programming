cmake_minimum_required(VERSION 3.29)
project(Lab4 C)

set(CMAKE_C_STANDARD 17)

find_package(OpenMP REQUIRED)
if(NOT OpenMP_C_FOUND)
    message(SEND_ERROR "Failed to find OpenMP.")
    return()
endif()

set(CMAKE_C_FLAGS "-fopenmp")

add_executable(Lab4
        include/checkOMP.h
        src/check_omp.c
        src/main.c
        include/lockExample.h
        src/lockExample.c
        include/scheduleExample.h
        src/scheduleExample.c)

target_link_libraries(Lab4 PRIVATE OpenMP::OpenMP_C)