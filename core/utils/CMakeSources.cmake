### Sources for the utils module

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/core/utils)

set(MODULE_PUBLIC_HEADERS
        ${MODULE_PATH}/Color.hpp
        ${MODULE_PATH}/ColorEnum.hpp
        ${MODULE_PATH}/Enums.hpp
        ${MODULE_PATH}/Guard.hpp
        ${MODULE_PATH}/LexicalCast.hpp
        ${MODULE_PATH}/NonCopyable.hpp
        ${MODULE_PATH}/NonMovable.hpp
        ${MODULE_PATH}/Relational.hpp
        ${MODULE_PATH}/Singleton.hpp
        ${MODULE_PATH}/Utils.hpp
        )

set(MODULE_PRIVATE_HEADERS
        ${MODULE_PATH}/details/UnixColor.hpp
        ${MODULE_PATH}/details/WindowsColor.hpp
        ${MODULE_PATH}/details/Color.hpp
        )

set(MODULE_SOURCES ${MODULE_PUBLIC_HEADERS} ${MODULE_PRIVATE_HEADERS})
