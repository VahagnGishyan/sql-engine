
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

project(sql-engine-query-parser)
set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

##########################################################

set (WIN_FLEX_BISON_DIR "C:/Users/User/.conan2/p/b/winfl74723ccb09fb6/p")
set (WIN_FLEX_BISON_BIN_DIR "${WIN_FLEX_BISON_DIR}/bin")
set (WIN_FLEX_BISON_INCLUDE_DIR "${WIN_FLEX_BISON_DIR}/include")
set (WIN_FLEX_EXECUTABLE "${WIN_FLEX_BISON_BIN_DIR}/win_flex.exe")
set (WIN_BISON_EXECUTABLE "${WIN_FLEX_BISON_BIN_DIR}/win_bison.exe")

include_directories( 
    ${WIN_FLEX_BISON_INCLUDE_DIR}/
)

set(LexerSource flex-scanner.l)
# set(ParserSource parser.y)

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp
#     COMMAND ${WIN_FLEX_EXECUTABLE}
#     ARGS --outfile=${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${LexerSource}
#     MAIN_DEPENDENCY ${LexerSource}
# )

# message("vgishyan: ${WIN_FLEX_BISON_INCLUDE_DIR}")

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
#     COMMAND ${WIN_BISON_EXECUTABLE}
#     ARGS --output=${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c -d ${CMAKE_CURRENT_SOURCE_DIR}/${ParserSource}
#     MAIN_DEPENDENCY ${ParserSource}
# )

# Add the generated files to your executable
set(SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cpp
    # ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c

    lexer.cpp
    main.cpp
)

##########################################################

add_library (${PROJECT_NAME} SHARED #STATIC 
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} 
    fmt::fmt
    sql-engine-app-info 
    sql-engine-utility 
    sql-engine-logging
    sql-engine-interface
    sql-engine-database
    sql-engine-sql-operations
)

add_compile_definitions(DB_QUERY_EXECUTOR_BUILD)

##########################################################
