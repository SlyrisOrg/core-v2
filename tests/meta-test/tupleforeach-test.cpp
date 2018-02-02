//
// Created by doom on 02/02/18.
//

#include <gtest/gtest.h>
#include <core/meta/TupleForEach.hpp>

TEST(Meta, TupleForEach)
{
    std::tuple<int, int, int> t{0, 1, 2};
    int cur = 0;

    meta::tuple_for_each(t, [&cur](int value) {
        ASSERT_EQ(cur, value);
        ++cur;
    });
    ASSERT_EQ(cur, 3);
}
