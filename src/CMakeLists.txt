cmake_minimum_required(VERSION 3.10)
project(TreeB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

# Include source directories
include_directories(src)
include_directories(src/headers)
include_directories(src/templates)

# Add source files
add_library(TreeB src/EmptyQueue.cpp)

# Add executable for main
add_executable(main src/main.cpp)
target_link_libraries(main TreeB)

# Add test executable
add_executable(test_tree_b tests/test_tree_b.cpp)
target_link_libraries(test_tree_b gtest gtest_main pthread TreeB)

# Add tests
add_test(NAME test_tree_b COMMAND test_tree_b)
