### Sources for the lib module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core/lib)

set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/Alias.hpp
        ${MODULE_PATH}/Exceptions.hpp
        ${MODULE_PATH}/GetSymbol.hpp
        ${MODULE_PATH}/Lib.hpp
        ${MODULE_PATH}/SharedLibrary.hpp
        )


set(MODULE_PRIVATE_HEADERS
        ${MODULE_PATH}/details/LoadingMode.hpp
        )

if (UNIX)
    set(MODULE_PRIVATE_HEADERS ${MODULE_PRIVATE_HEADERS}
            ${MODULE_PATH}/details/PosixSharedLibrary.hpp
            )
endif (UNIX)

if (WIN32)
    set(MODULE_PRIVATE_HEADERS ${MODULE_PRIVATE_HEADERS}
            ${MODULE_PATH}/details/WindowsSharedLibrary.hpp
            )

endif (WIN32)

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
