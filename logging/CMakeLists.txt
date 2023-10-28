
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

project(sql-engine-logging)

find_package(fmt REQUIRED)

include_directories( 
    ../application-info/
    ../utility/
)

set(SOURCES
    console-log.cpp
    easy-log.cpp
    file-log.cpp
    ilogger.cpp
    logging.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(LOGGING_SHARE)

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    sql-engine-utility 
    sql-engine-application-info 
    fmt::fmt
)
