### Sources for the algorithm module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core/algorithm)

set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/erase_if.hpp)

set(MODULE_PRIVATE_HEADERS "")

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
