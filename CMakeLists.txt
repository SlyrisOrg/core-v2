if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif()

cmake_minimum_required(VERSION 3.9)

##! Prerequisites CTEST
enable_testing()

##! Project Name
project(core)

##! Module Path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

##! Project Module Path
set(CORE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_config)

##! CMake Library Include
include(${CMAKE_MODULE_PATH}/library.cmake)

##! CMake Project Configuration include
include(${CORE_MODULE_PATH}/${PROJECT_NAME}.cmake)

##! Project Options
option(CORE_BUILD_TESTS "Build tests of Core C++ Library" OFF)
option(CORE_BUILD_DEMO "Build the demo of Core C++ Library" OFF)

add_subdirectory(core)

##! Project Tests
if (CORE_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

##! Demo project, contains all the documented examples.
if (CORE_BUILD_DEMO)
    set(CORE_DEMO_PATH ${CMAKE_SOURCE_DIR}/demo)
    add_subdirectory(demo)
endif()