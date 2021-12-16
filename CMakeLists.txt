cmake_minimum_required(VERSION 3.21.3)
project(nixcalcpp VERSION 0.1 LANGUAGES CXX)

# Adding libraries
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/calc/)

# Adding executable
add_executable(nixcalcpp ${PROJECT_SOURCE_DIR}/bin/src/nixcalcpp.cpp)

# Linking libraries
target_link_libraries(nixcalcpp PUBLIC calculator)
