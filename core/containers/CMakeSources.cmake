### Sources for the containers module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core/containers)

set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/Span.hpp
        )

set(MODULE_PRIVATE_HEADERS "")

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
