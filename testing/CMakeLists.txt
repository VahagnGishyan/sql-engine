
cmake_minimum_required(VERSION 3.0)
project(sql-engine-testing)

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(core)
add_subdirectory(utility-core)
add_subdirectory(utility-filesystem)
