
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-utility)

find_package(fmt REQUIRED)

set(SOURCES
    core.cpp
    filesystem.cpp
    options.cpp
)

set(HEADERS
    core.hpp
    filesystem.hpp
    options.hpp
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

add_compile_definitions(UTILITY_BUILD)

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
