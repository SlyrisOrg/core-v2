include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(Core::Reflection "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(Core-Reflection INTERFACE Core::PP Core::Meta)
