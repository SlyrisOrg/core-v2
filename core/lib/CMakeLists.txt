include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(Core::Lib "${MODULE_SOURCES}" ${MODULE_PATH})

if (LINUX)
    target_link_libraries(Core-Lib INTERFACE Core::Config ${CMAKE_DL_LIBS} stdc++fs)
endif(LINUX)

if(APPLE)
    target_link_libraries(Core-Lib INTERFACE Core::Config ${CMAKE_DL_LIBS} /usr/local/opt/llvm/lib/libc++experimental.a)
endif(APPLE)

if (WIN32)
    target_link_libraries(Core-Lib INTERFACE Core::Config)
endif(WIN32)
