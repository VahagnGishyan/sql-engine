
cmake_minimum_required(VERSION 3.0)

project(run-tests)

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

# set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-format.cmake)
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-tidy.cmake)

set(SOURCES
    runner/main.cpp

    dir-preparator/dir-impl.cpp
    dir-preparator/file-impl.cpp
    dir-preparator/preparator.cpp

    utility/core.cpp
    utility/dir-exists.cpp
    utility/empty-dir.cpp
    utility/file-exists.cpp
    utility/file-extension.cpp
    utility/list-dir.cpp
    utility/make-remove.cpp
    utility/options.cpp
    utility/path-exists.cpp
    utility/test-dir-preparation.cpp

    database/test-column.cpp
    database/test-table.cpp
    database/test-database.cpp
    database/test-row-oriented-table.cpp
    database/utility.cpp

    local-database/test-db-local-json-reader.cpp
    local-database/test-db-local-json-writer.cpp
    local-database/utility.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt 
    gtest::gtest

    sql-engine-utility 
    sql-engine-app-info 
    sql-engine-logging
    sql-engine-interface
    sql-engine-database
    sql-engine-local-database
)

