
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-table)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

set(SOURCES
    # column.cpp
    dyn-object.cpp
    dyn-value.cpp
    row-element.cpp
    # table.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(DB_TABLE_BUILD)

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt
    sql-engine-utility 
    sql-engine-app-info 
    sql-engine-logging
    sql-engine-interface
)

##########################################################
