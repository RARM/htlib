cmake_minimum_required(VERSION 3.14)
project(htlib)

# Set compiler flags
set(CMAKE_CXX_STANDARD 11)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Create htlib library
add_library(htlib STATIC src/htlib.c)
target_include_directories(htlib PUBLIC src)

# Create test executable
add_executable(htlib_test test/test.cpp)
target_link_libraries(htlib_test gtest_main gtest htlib)