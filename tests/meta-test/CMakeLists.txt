set(SOURCES
        typelist-test.cpp
        prioritytag-test.cpp
        typetraits-test.cpp
        tupleforeach-test.cpp
        visitor-test.cpp
        map-test.cpp
        )
CREATE_UNIT_TEST(meta-test Core: "${SOURCES}")
target_link_libraries(meta-test Core::Meta)
