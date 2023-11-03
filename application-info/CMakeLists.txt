
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-application-info)

set(SOURCES
    application.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
    sql-engine-utility 
)
