include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(Core::Meta "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(Core-Meta INTERFACE Core::Config Core::PP)
