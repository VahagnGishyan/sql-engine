
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-logging)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

include_directories( 
    # ../application-info/
    ../
)

set(SOURCES
    fmt-log.cpp
    log-core.cpp
    logging.cpp
    main.cpp
)

# add_library (${PROJECT_NAME} SHARED #STATIC 
    # ${SOURCES}
# ) 

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# add_compile_definitions(LOGGING_SHARE)

target_link_libraries(${PROJECT_NAME} 
    # sql-engine-utility 
    # sql-engine-application-info 
    fmt::fmt
)
