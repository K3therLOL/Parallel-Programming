cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)

add_executable(Lab7_tests test-main.cpp test.cpp)

target_link_libraries(Lab7_tests PRIVATE OpenMP::OpenMP_CXX)

target_link_libraries(Lab7_tests PRIVATE MPI::MPI_CXX)

target_link_libraries(Lab7_tests PRIVATE Catch2::Catch2)

target_link_libraries(Lab7_tests PRIVATE m)
