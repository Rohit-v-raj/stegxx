cmake_minimum_required(VERSION 3.18)
project(steg++)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wshadow -Wextra -Werror -Wsign-conversion)

add_compile_definitions(LOG_LEVEL=3)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()
message(STATUS "Generating with build type: ${CMAKE_BUILD_TYPE}")

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)

enable_testing()
add_test(NAME run_tests COMMAND run_tests)
