
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.0)
project(sql-engine)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(utility)
add_subdirectory(observer)
