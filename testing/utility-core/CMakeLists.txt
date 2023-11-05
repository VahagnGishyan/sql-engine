
cmake_minimum_required(VERSION 3.0)

project(testing-utility-core)

set(SOURCES
    main.cpp
)

##########################################################

set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/auto-format.cmake)
AutoFormatClang(${FORMAT_FILES})

##########################################################

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt 
    gtest::gtest
    sql-engine-utility
    sql-engine-testing-core
)
