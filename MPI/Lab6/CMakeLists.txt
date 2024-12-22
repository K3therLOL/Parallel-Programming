cmake_minimum_required(VERSION 3.30)
project(Lab6 C)

set(CMAKE_C_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(Lab6 main.c
        include/timeShellSort.h
        src/randomaizer.c
        include/randomaizer.h
        include/ShellSort.h
        src/shellSort.c)

target_link_libraries(Lab6 PUBLIC MPI::MPI_C)