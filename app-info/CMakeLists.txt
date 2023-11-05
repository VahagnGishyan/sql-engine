
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

project(sql-engine-app-info)

add_compile_definitions(APP_INFO_BUILD)

set(SOURCES
    application.cpp
)

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
) 

target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} 
    sql-engine-utility 
)
