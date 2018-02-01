set(SOURCES log-test.cpp)
CREATE_UNIT_TEST(log-test Core: "${SOURCES}")
target_link_libraries(log-test Core::Log)
