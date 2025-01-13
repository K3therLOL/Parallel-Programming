cmake_minimum_required(VERSION 3.28)
project(Lab3 C CXX)

set(CMAKE_C_STANDARD 23)

find_package(OpenMP REQUIRED)
if(NOT OpenMP_C_FOUND)
    message(SEND_ERROR "Failed to find OpenMP.")
    return()
endif()

set(CMAKE_C_FLAGS "-fopenmp")

set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(Lab3 main.c
                    src/shellSort.c
                    include/shellSort.h
                    include/randomaizer.h
                    src/randomaizer.c
                    include/timer.h
                    src/timer.c)

target_link_libraries(Lab3 PRIVATE OpenMP::OpenMP_C)

add_subdirectory(tests)
