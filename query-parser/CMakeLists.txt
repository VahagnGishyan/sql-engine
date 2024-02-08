
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-query-parser)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

set(SOURCES
    lexer.cpp
    # parser.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(DB_QUERY_EXECUTOR_BUILD)

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt
    sql-engine-app-info 
    sql-engine-utility 
    sql-engine-logging
    sql-engine-interface
    sql-engine-database
    sql-engine-sql-operations
)

##########################################################
