### Sources for the config module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core/config)
set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/CompilerHints.hpp
        ${MODULE_PATH}/Environment.hpp
        )

set(MODULE_PRIVATE_HEADERS "")

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
