
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-local-database)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

set(SOURCES
    db-local-json-reader.cpp
    db-local-json-writer.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(DB_MANAGER_BUILD)

target_link_libraries(${PROJECT_NAME} 
    sql-engine-utility 
    sql-engine-app-info 
    sql-engine-logging
    sql-engine-interface
    sql-engine-database
    fmt::fmt
    Boost::boost
    Boost::filesystem
    Boost::log
)

##########################################################
