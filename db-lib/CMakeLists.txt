
cmake_minimum_required(VERSION 3.0)
project(sql-engine-db-main)

find_package(fmt REQUIRED)
find_package(GTest REQUIRED)

include_directories(
    interface
)

set (DBM_SUBDIRS
    # db-manager
    # database
    # filestream
    interface
)

# set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-format.cmake)
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-tidy.cmake)

FOREACH(subdir ${DBM_SUBDIRS})
    message("[${PROJECT_NAME}] subdir: ${subdir}")
    ClangFormatDir(${CMAKE_CURRENT_LIST_DIR}/${subdir})
    # ClangTidyDir(${subdir})
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${subdir})
ENDFOREACH()
