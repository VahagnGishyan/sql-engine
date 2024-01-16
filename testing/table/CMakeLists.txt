
cmake_minimum_required(VERSION 3.0)

project(testing-table)

set(SOURCES
    main.cpp
    test-column-element.cpp
    # test-column.cpp
    # test-dyn-object.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt 
    gtest::gtest
    sql-engine-utility
    sql-engine-table
)
