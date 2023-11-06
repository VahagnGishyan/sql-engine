
function(GetCppBasedFilesInDir)
    if (EXISTS ${ARGV0})
        file(GLOB CPP_FILES
            "${ARGV0}/*.cpp" 
            "${ARGV0}/*.cc" 
            "${ARGV0}/*.c" 
            "${ARGV0}/*.hpp" 
            "${ARGV0}/*.h" 
            "${ARGV0}/*.cxx" 
            "${ARGV0}/*.hxx"
        )
        set(CppBasedFiles ${CPP_FILES} PARENT_SCOPE)
    elseif()
        message(SEND_ERROR "dir-path: ${ARGV0} does not exists")
    endif()
endfunction()

function(AssertFilesExists)
    foreach(file ${ARGN})
        if (NOT EXISTS ${file})
            message(SEND_ERROR "file-path: ${file} does not exists")
        endif()
    endforeach()
endfunction()
