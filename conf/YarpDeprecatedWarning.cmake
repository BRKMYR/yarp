macro(YARP_DEPRECATED_WARNING)
    if(NOT YARP_NO_DEPRECATED_WARNINGS)
        message(WARNING "${ARGN}")
    endif(NOT YARP_NO_DEPRECATED_WARNINGS)
endmacro()