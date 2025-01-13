cmake_minimum_required(VERSION 3.29)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)
if(NOT OpenMP_CXX_FOUND)
        message(SEND_ERROR "Failed to find OpenMP.")
        return()
endif()

set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(Lab2
        src/main.cpp
        src/search.cpp
        src/randomaizer.cpp
        include/ompCancellation.h
        src/ompCancellation.cpp
        src/timeAlgorithm.cpp
        include/timeAlgorithm.h
        )


add_executable(Lab2_tests
        src/search.cpp
        src/randomaizer.cpp
        tests/lab2Tests.cpp
        tests/Catch/binarySearch.cpp)

target_link_libraries(Lab2 PRIVATE OpenMP::OpenMP_C)