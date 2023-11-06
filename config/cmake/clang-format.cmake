
include("${CMAKE_SOURCE_DIR}/config/cmake/utility.cmake")

# Define a custom function that takes a list of files as an argument
function(ClangFormatFiles)
    if(ENABLE_CLANG_FORMAT)
        AssertFilesExists(${ARGN})
        foreach(file ${ARGN})
            message("Auto clang-format file: ${file}")
            execute_process(
                COMMAND clang-format -i ${file}
            )
        endforeach()
    endif()
endfunction()

function(ClangFormatDir)
    GetCppBasedFilesInDir(${ARGV0})
    ClangFormatFiles(${CppBasedFiles})
endfunction()
