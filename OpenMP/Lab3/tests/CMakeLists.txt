set(CMAKE_CXX_STANDARD 20)

target_link_libraries(Lab3 PRIVATE OpenMP::OpenMP_CXX)

add_executable(Lab3_tests lab3Tests.cpp)