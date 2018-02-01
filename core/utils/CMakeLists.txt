include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(Core::Utils "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(Core-Utils INTERFACE Core::PP Core::Config)
