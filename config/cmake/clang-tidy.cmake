
include("${CMAKE_SOURCE_DIR}/config/cmake/utility.cmake")

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)

    if(NOT CLANG_TIDY_COMMAND)
        message(WARNING "🔴 CMake_RUN_CLANG_TIDY is ON but clang-tidy is not found!")
        set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)
    else()
        message(STATUS "🟢 CMake_RUN_CLANG_TIDY is ON")
        set(CLANGTIDY_EXTRA_ARGS
            "-extra-arg=-Wno-unknown-warning-option"
    )
    endif()
endif()

function(ClangTidyDir)
    GetCppBasedFilesInDir(${ARGV0})
    AssertFilesExists(${CppBasedFiles})
    set (CLANG_TIDY_FLAGS "-format-style=file" "-clang-analyzer-cplusplus" "-extra-arg=-std=c++17")
    message(STATUS "clang-tidy ${CLANG_TIDY_FLAGS} -header-filter=${ARGV0} ${CppBasedFiles}")
    execute_process(
        COMMAND clang-tidy ${CLANG_TIDY_FLAGS} -header-filter=${ARGV0} ${CppBasedFiles}
    )
endfunction()
