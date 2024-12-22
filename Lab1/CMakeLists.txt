cmake_minimum_required(VERSION 3.30)
project(Lab1 C)

set(CMAKE_C_STANDARD 17)

find_package(OpenMP REQUIRED)

set(CMAKE_C_FLAGS "-fopenmp")


add_executable(Lab1 main.c
        src/OMPcheck.c
        src/max.c
        src/randomaizer.c
        src/timeMax.c
        include/OMPcheck.h
        include/max.h
        include/randomaizer.h
        include/timeMax.h)

target_link_libraries(Lab1 PRIVATE OpenMP::OpenMP_C)