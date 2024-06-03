cmake_minimum_required(VERSION 3.10)
project(TreeB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")

# Add GoogleTest
enable_testing()
find_package(GTest REQUIRED)
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
target_link_libraries(test_tree_b ${GTEST_LIBRARIES} pthread TreeB)

# Add tests
add_test(NAME test_tree_b COMMAND test_tree_b)
