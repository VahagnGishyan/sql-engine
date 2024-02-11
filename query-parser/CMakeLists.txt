
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

project(sql-engine-query-parser)
set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

##########################################################

set(SOURCES
    json-queries-file-parser.cpp
)

##########################################################

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt
    Boost::boost
    Boost::filesystem
    Boost::log
    sql-engine-app-info 
    sql-engine-utility 
    sql-engine-logging
    sql-engine-interface
    # sql-engine-database
    sql-engine-query
)

add_compile_definitions(QUERY_PARSER_BUILD)

##########################################################
