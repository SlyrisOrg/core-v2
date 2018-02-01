set(SOURCES pp-test.cpp)
CREATE_UNIT_TEST(pp-test Core: "${SOURCES}")
target_link_libraries(pp-test Core::PP)
