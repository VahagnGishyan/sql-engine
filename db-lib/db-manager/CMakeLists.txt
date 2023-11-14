
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-db-manager)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

set(SOURCES
    db-manager-info.cpp
    db-manager-init.cpp
    db-manager.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(DB_MANAGER_BUILD)

target_link_libraries(${PROJECT_NAME} 
    sql-engine-utility 
    sql-engine-app-info 
    sql-engine-logging
    sql-engine-db-interface
    sql-engine-db-db
    fmt::fmt
)

##########################################################
