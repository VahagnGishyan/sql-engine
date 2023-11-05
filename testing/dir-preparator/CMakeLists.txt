
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(testing-dir-preparator)

find_package(fmt REQUIRED)

set(SOURCES
    dir-impl.cpp
    file-impl.cpp
    preparator.cpp
)

set(HEADERS
    impl.hpp
    preparator.hpp
    sharelib.cpp
)

##########################################################

set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/auto-format.cmake)
AutoFormatClang(${FORMAT_FILES})

##########################################################

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

add_compile_definitions(TEST_DIR_PREPARATOR)

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt
    sql-engine-utility
)
