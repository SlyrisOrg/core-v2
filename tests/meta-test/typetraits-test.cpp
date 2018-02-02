//
// Created by doom on 02/02/18.
//

#include <gtest/gtest.h>
#include <core/meta/TypeTraits.hpp>

TEST(Meta, IsComparableWith)
{
    ASSERT_TRUE((meta::is_eq_comparable_with_v<std::string, const char *>));
    ASSERT_FALSE((meta::is_eq_comparable_with_v<std::string, int>));
}
