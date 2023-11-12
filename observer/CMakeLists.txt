
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(observer)

find_package(fmt REQUIRED)

include_directories( 
    ../
)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt 
    sql-engine-utility
    sql-engine-logging
    # sql-engine-db-manager
    sql-engine-db-interface
)
