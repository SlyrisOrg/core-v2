set(SOURCES config-test.cpp)
CREATE_UNIT_TEST(config-test modulename: "${SOURCES}")
target_link_libraries(config-test Core::Config)
