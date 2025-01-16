cmake_minimum_required(VERSION 3.28)
project(Lab5 C)

set(CMAKE_C_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(Lab5 main.c
        src/MPIcheck.c
        src/max.c
        src/randomaizer.c
        src/timeMax.c
        include/MPIcheck.h
        include/max.h
        include/randomaizer.h
        include/timeMax.h)

target_link_libraries(Lab5 PUBLIC MPI::MPI_C)
