
##! Macro for get all the subdirectory of the current directory
macro(SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach (child ${children})
        if (IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif ()
    endforeach ()
    set(${result} ${dirlist})
endmacro()