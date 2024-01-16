
cmake_minimum_required(VERSION 3.0)
project(sql-engine-testing)

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)


set (TEST_SUBDIRS
    dir-preparator

    table

    utility-core
    utility-filesystem
)

# set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-format.cmake)
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-tidy.cmake)

FOREACH(subdir ${TEST_SUBDIRS})
    message("[${PROJECT_NAME}] subdir: ${subdir}")
    ClangFormatDir(${CMAKE_CURRENT_LIST_DIR}/${subdir})
    # ClangTidyDir(${subdir})
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${subdir})
ENDFOREACH()
