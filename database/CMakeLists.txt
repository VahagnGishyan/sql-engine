
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-database)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

set(SOURCES
    database.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(DB_DATABASE_BUILD)

target_link_libraries(${PROJECT_NAME} 
    sql-engine-utility 
    sql-engine-app-info 
    sql-engine-logging
    sql-engine-interface
    sql-engine-table
    fmt::fmt
)

##########################################################
