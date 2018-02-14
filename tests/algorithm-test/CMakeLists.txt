set(SOURCES algorithm-test.cpp)
CREATE_UNIT_TEST(algorithm-test Core: "${SOURCES}")
target_link_libraries(algorithm-test Core::Algorithm)