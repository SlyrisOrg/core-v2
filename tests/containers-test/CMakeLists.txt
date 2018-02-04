set(SOURCES span-test.cpp ringbuffer-test.cpp)
CREATE_UNIT_TEST(containers-test Core: "${SOURCES}")
target_link_libraries(containers-test Core::Containers)
