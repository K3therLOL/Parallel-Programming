cmake_minimum_required(VERSION 3.27)

project(Lab1 C)

set(CMAKE_C_STANDARD 11)

find_package(OpenMP REQUIRED)

set(CMAKE_C_FLAGS "-fopenmp")

add_executable(Lab1 src/main.c
        include/OMPcheck.h
        include/max.h
        include/randomaizer.h
        include/time_max.h
        src/OMPcheck.c
        src/max.c
        src/randomaizer.c
        src/time_max.c)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY D:/ClionProjects/Lab4/lib)

add_library(max SHARED src/max.c src/randomaizer.c)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_C
                                      PUBLIC  max)