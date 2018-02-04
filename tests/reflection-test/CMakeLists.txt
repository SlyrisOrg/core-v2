set(SOURCES reflection-test.cpp)
CREATE_UNIT_TEST(reflection-test Core: "${SOURCES}")
target_link_libraries(reflection-test Core::Reflection)
