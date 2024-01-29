
cmake_minimum_required(VERSION 3.0)

project(testing-utility)

set(SOURCES
    run-test.cpp

    dir-exists.cpp
    empty-dir.cpp
    file-exists.cpp
    file-extension.cpp
    list-dir.cpp
    make-remove.cpp
    options.cpp
    path-exists.cpp
    test-dir-preparation.cpp
    core.cpp
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
    sql-engine-app-info 
    sql-engine-utility 
    testing-dir-preparator
)
