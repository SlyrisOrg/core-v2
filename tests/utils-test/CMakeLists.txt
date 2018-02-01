set(SOURCES utils-test.cpp enums-test.cpp relational-test.cpp guard-test.cpp lexicalcast-test.cpp)
CREATE_UNIT_TEST(utils-test Core: "${SOURCES}")
target_link_libraries(utils-test Core::Utils)
