cmake_minimum_required(VERSION 3.16)
project(rybinsk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(rybinsk
    src/peal.cpp
    src/voice.cpp
    src/night.cpp
)
target_include_directories(rybinsk PUBLIC include)

add_executable(rybinsk_tests
    tests/main.cpp
    tests/test_life.cpp
    tests/test_assign.cpp
    tests/test_ops.cpp
    tests/test_voice.cpp
    tests/test_night.cpp
)
target_include_directories(rybinsk_tests PRIVATE tests)
target_link_libraries(rybinsk_tests PRIVATE rybinsk)

if(MSVC)
    target_compile_options(rybinsk PRIVATE /W4)
    target_compile_options(rybinsk_tests PRIVATE /W4)
else()
    target_compile_options(rybinsk PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
    target_link_options(rybinsk PUBLIC -fsanitize=address)
    target_compile_options(rybinsk_tests PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
endif()