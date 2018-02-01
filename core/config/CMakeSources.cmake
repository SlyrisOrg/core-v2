### Sources for the config module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core/config)
set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/PlatformConfig.hpp
        ${MODULE_PATH}/CompilerConfig.hpp
        ${MODULE_PATH}/Config.hpp
        )

set(MODULE_PRIVATE_HEADERS "")

if (WIN32)
    set(MODULE_PRIVATE_HEADERS
            ${MODULE_PRIVATE_HEADERS}
            ${MODULE_PATH}/details/WindowsConfig.hpp)
endif (WIN32)

if (APPLE)
    set(MODULE_PRIVATE_HEADERS ${MODULE_PRIVATE_HEADERS} ${MODULE_PATH}/details/OSXConfig.hpp)
endif (APPLE)

if (UNIX)
    set(MODULE_PRIVATE_HEADERS ${MODULE_PRIVATE_HEADERS} ${MODULE_PATH}/details/UnixConfig.hpp)
endif (UNIX)

if (LINUX)
    set(MODULE_PRIVATE_HEADERS ${MODULE_PRIVATE_HEADERS} ${MODULE_PATH}/details/LinuxConfig.hpp)
endif (LINUX)

if (CLANG)
    set(MODULE_PRIVATE_HEADERS ${MODULE_PRIVATE_HEADERS} ${MODULE_PATH}/details/Clang.hpp)
endif (CLANG)

if (GCC)
    set(MODULE_PRIVATE_HEADERS ${MODULE_PRIVATE_HEADERS} ${MODULE_PATH}/details/Gcc.hpp)
endif (GCC)

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
