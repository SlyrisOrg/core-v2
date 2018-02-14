include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(Core::Containers "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(Core-Containers INTERFACE Core::Config Core::Utils Core::Meta)
