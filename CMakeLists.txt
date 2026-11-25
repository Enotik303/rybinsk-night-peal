cmake_minimum_required(VERSION 3.16)
project(rostov LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(rostov
    src/peal.cpp
    src/night.cpp
)
target_include_directories(rostov PUBLIC include)
target_compile_options(rostov PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
target_link_options(rostov PUBLIC -fsanitize=address)

add_executable(rostov_tests
    tests/main.cpp
    tests/test_life.cpp
    tests/test_assign.cpp
    tests/test_ops.cpp
    tests/test_night.cpp
)
target_include_directories(rostov_tests PRIVATE tests)
target_link_libraries(rostov_tests PRIVATE rostov)
target_compile_options(rostov_tests PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
