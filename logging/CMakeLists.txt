
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-logging)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

include_directories( 
    ../
)

set(SOURCES
    fmt-log.cpp
    log-core.cpp
    logging.cpp
)

set(HEADERS
    fmt-log.hpp
    ilogger.hpp
    log-core.hpp
    logging.hpp
    sharelib.hpp
)

##########################################################

set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/auto-format.cmake)
AutoFormatClang(${FORMAT_FILES})

##########################################################

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(LOGGING_BUILD)

target_link_libraries(${PROJECT_NAME} 
    sql-engine-utility 
    sql-engine-app-info 
    fmt::fmt
)

##########################################################
