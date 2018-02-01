//
// Created by doom on 01/02/18
//

#include <gtest/gtest.h>
#include <core/pp/PP.hpp>

TEST(Preprocessing, CountArgs)
{
    ASSERT_EQ(pp_count_args(1, 2, 3, 4, 5), 5);

    ASSERT_EQ(pp_count_args(1), 1);
}

#define doubleParam(a)      (a * 2),
#define incrementIBy(nb)    i += nb;

TEST(Preprocessing, ForEach)
{
    std::vector<int> v{pp_for_each(doubleParam, 1, 2, 3)};

    ASSERT_EQ(v.size(), 3u);
    ASSERT_EQ(v[0], 2);
    ASSERT_EQ(v[1], 4);
    ASSERT_EQ(v[2], 6);

    int i = 0;
    pp_for_each(incrementIBy, 1, 2, 3);
    ASSERT_EQ(i, 6);
}
#undef doubleParam

TEST(Preprocessing, Stringify)
{
    const char *str = pp_stringify(hello);
    ASSERT_STREQ(str, "hello");

    const char *str2 = pp_stringify(hello aa);
    ASSERT_STREQ(str2, "hello aa");
}

TEST(Preprocessing, Stringviewify)
{
    constexpr std::string_view sv = pp_stringviewify(hello);
    ASSERT_EQ(sv, std::string_view("hello"));

    constexpr std::string_view sv2 = pp_stringviewify(hello aa);
    ASSERT_EQ(sv2, std::string_view("hello aa"));
}

TEST(Preprocessing, Paste)
{
    int var1 = 1;

    pp_paste(var, 1) = 2;
    ASSERT_EQ(var1, 2);
}

TEST(Preprocessing, Args)
{
    int n;

    n = pp_first_arg(1, 2, 3, 4, 5);
    ASSERT_EQ(n, 1);
}
