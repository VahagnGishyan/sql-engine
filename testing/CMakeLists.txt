
cmake_minimum_required(VERSION 3.0)
project(sql-engine-testing)

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

set(SOURCES
    utility-core/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} fmt::fmt sql-engine-utility gtest::gtest)

add_test(NAME utility-core COMMAND ${PROJECT_NAME})
