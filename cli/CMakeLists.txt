
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-cli)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

set(SOURCES
    cli-operations.cpp
    input-parser.cpp
    io-manager.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt 
    Boost::boost
    Boost::program_options

    sql-engine-utility
    sql-engine-logging
    sql-engine-interface
    sql-engine-local-database
    sql-engine-debug-db
    sql-engine-query-parser
)

##########################################################
