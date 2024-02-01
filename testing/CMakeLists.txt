
##################################
#                                #
##################################

cmake_minimum_required(VERSION 3.0)
project(run-tests)
enable_testing()

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

# set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-format.cmake)
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-tidy.cmake)

##################################
#                                #
##################################

add_executable(tester-utility 
    dir-preparator/dir-impl.cpp
    dir-preparator/file-impl.cpp
    dir-preparator/preparator.cpp

    utility/main.cpp
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
)
target_link_libraries(tester-utility 
    fmt::fmt 
    gtest::gtest
    sql-engine-interface
    sql-engine-local-database
)
target_compile_features   (tester-utility PRIVATE cxx_std_17)
target_include_directories(tester-utility PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(tester-utility PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


##################################
#                                #
##################################

add_executable(tester-database 
    database/main.cpp
    database/test-column.cpp
    database/test-table.cpp
    database/test-database.cpp
    database/test-row-oriented-table.cpp
    database/utility.cpp
)
target_link_libraries(tester-database 
    fmt::fmt 
    gtest::gtest
    sql-engine-interface
    sql-engine-database
)
target_compile_features   (tester-database PRIVATE cxx_std_17)
target_include_directories(tester-database PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(tester-database PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

##################################
#                                #
##################################

add_executable(tester-local-database
    local-database/test-db-local-json-reader.cpp
    local-database/test-db-local-json-writer.cpp
    local-database/test-local-database.cpp
    local-database/test-table-column.cpp
    local-database/utility.cpp
)
target_link_libraries(tester-local-database 
    fmt::fmt 
    gtest::gtest
    sql-engine-utility
    sql-engine-interface
    sql-engine-local-database
)
target_compile_features   (tester-local-database PRIVATE cxx_std_17)
target_include_directories(tester-local-database PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(tester-local-database PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

##################################
#                                #
##################################

add_test(NAME tester-utility
        COMMAND tester-utility)
add_test(NAME tester-database
         COMMAND tester-database)
add_test(NAME tester-local-database
        COMMAND tester-local-database)

##################################
#                                #
##################################
