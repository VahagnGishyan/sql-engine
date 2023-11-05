
# Define a custom function that takes a list of files as an argument
function(AutoFormatClang)
    set(FILE_PATH ${CMAKE_CURRENT_LIST_DIR})
    foreach(file ${ARGN})
        set(filepath ${FILE_PATH}/${file})
        message("Auto clang-format file: ${filepath}")
        execute_process(
            COMMAND clang-format -i ${filepath}
            RESULT_VARIABLE script_result
            OUTPUT_VARIABLE script_output
            ERROR_VARIABLE script_error
        )
    endforeach()
endfunction()
