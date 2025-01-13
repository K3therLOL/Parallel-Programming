set(CMAKE_CXX_STANDARD 20)

add_executable(Lab6_tests lab6Tests.cpp)

target_link_libraries(Lab6_tests PRIVATE MPI::MPI_CXX)