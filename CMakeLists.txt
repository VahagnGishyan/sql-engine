
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)
project(sql-engine)

enable_testing()

include_directories( 
    ./
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(${CMAKE_SOURCE_DIR}/config/cmake/clang-format.cmake)
include(${CMAKE_SOURCE_DIR}/config/cmake/clang-tidy.cmake)
include(${CMAKE_SOURCE_DIR}/config/cmake/user-settings.cmake)

set (SUBDIRS
    app-info
    cli
    database
    local-database
    interface
    logging
    observer
    query
    query-parser
    # sql-engine
    # other
    debug-db
    utility
)

if (ENABLE_TESTING)
    set (SUBDIRS
        ${SUBDIRS}
        testing
    )
endif()


FOREACH(subdir ${SUBDIRS})
    message("[${PROJECT_NAME}] subdir: ${subdir}")
    ClangFormatDir(${subdir})
    # ClangTidyDir(${subdir})
    add_subdirectory(${subdir})
ENDFOREACH()
