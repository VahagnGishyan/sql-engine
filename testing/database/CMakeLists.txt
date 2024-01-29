
cmake_minimum_required(VERSION 3.0)

project(testing-database)

set(SOURCES
    run-test.cpp

    test-column.cpp
    test-table.cpp
    test-database.cpp
    test-row-oriented-table.cpp
    utility.cpp
)

add_library (${PROJECT_NAME} SHARED  
    ${SOURCES}
) 

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt 
    gtest::gtest
    sql-engine-utility
    sql-engine-database
)
