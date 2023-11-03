
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)
project(sql-engine)

enable_testing()

include_directories( 
    ./
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set (SUBDIRS
    app-info
    db-manager
    utility
    logging
    observer
    # other
)

# set(FORMAT_FILES ${SOURCES} ${HEADERS})
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-format.cmake)
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-tidy.cmake)

# set (ENABLE_CLANG_FORMAT "true")

FOREACH(subdir ${SUBDIRS})
    message("[${PROJECT_NAME}] subdir: ${subdir}")
    ClangFormatDir(${subdir})
    # ClangTidyDir(${subdir})
    add_subdirectory(${subdir})
ENDFOREACH()
