
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-db-stream)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

set(SOURCES
    db-stream.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(DB_STREAM_BUILD)

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt
    sql-engine-app-info 
    sql-engine-utility 
    sql-engine-logging
    sql-engine-interface
    sql-engine-db-manager
    sql-engine-filestream
)

##########################################################
