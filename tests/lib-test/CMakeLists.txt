set(SOURCES lib-test.cpp)
CREATE_UNIT_TEST(lib-test Core: "${SOURCES}")
target_link_libraries(lib-test Core::Lib Core::Utils)

add_library(testlib SHARED test/ITest.hpp test/Test.hpp test/Test.cpp)
add_library(test2lib SHARED test2/ITest2.hpp test2/Test2.hpp test2/Test2.cpp)
add_library(lollib SHARED lol/lol.c)

if (MSVC)
    set_target_properties(testlib PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

    set_target_properties(test2lib PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

    set_target_properties(lollib PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
elseif (GCC OR CLANG OR ICC)
    set_target_properties(testlib PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(test2lib PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(lollib PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif()

add_dependencies(lib-test testlib test2lib lollib)

target_link_libraries(testlib Core::Lib Core::Utils)
target_link_libraries(test2lib Core::Lib Core::Utils)
