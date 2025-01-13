cmake_minimum_required(VERSION 3.28)

project(Lab7 C CXX)

set(CMAKE_C_STANDARD 17)

find_package(OpenMP REQUIRED)

if(NOT OpenMP_C_FOUND)
    message(SEND_ERROR "Failed to find OpenMP.")
    return()
endif()

find_package(MPI REQUIRED)

if(NOT MPI_C_FOUND)
    message(SEND_ERROR "Failed to find MPI.")
    return()
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -Werror -fopenmp -lm")

add_executable(Lab7 main.c include/primeNumbers.h src/primeNumbers.c)

target_link_libraries(Lab7 PRIVATE OpenMP::OpenMP_C)

target_link_libraries(Lab7 PUBLIC MPI::MPI_C)

target_link_libraries(Lab7 PUBLIC m)

add_subdirectory(tests)
