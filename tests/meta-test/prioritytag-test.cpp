//
// Created by doom on 01/02/18.
//

#include <gtest/gtest.h>
#include <core/meta/PriorityTag.hpp>

template <typename T, std::enable_if_t<std::is_same_v<int, T>, bool> = true>
static int dummy([[maybe_unused]] T t, meta::PriorityTag<1>)
{
    return 1;
}

template <typename T>
static int dummy([[maybe_unused]] T unused, meta::PriorityTag<0>)
{
    return 2;
}

TEST(Meta, PriorityTag)
{
    ASSERT_EQ(dummy(-2, meta::PriorityTag<1>{}), 1);    //PriorityTag<1> and T = int    -> match with (1)
    ASSERT_EQ(dummy(3.2, meta::PriorityTag<1>{}), 2);   //PriorityTag<1> and T = float  -> match with (2)
    ASSERT_EQ(dummy(-2, meta::PriorityTag<0>{}), 2);    //PriorityTag<0> and T = int    -> match with (2)
}
