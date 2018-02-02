//
// Created by doom on 01/02/18.
//

#include <string_view>
#include <gtest/gtest.h>
#include <core/meta/Map.hpp>

TEST(Meta, Map)
{
    using namespace std::string_view_literals;
    auto map = meta::makeMap("salut"sv, 0, "lolol"sv, 1, "tralala"sv, 2);
    std::string s;
    int i = 0;
    auto l = [&s, &i](auto &&k, auto &&v) {
        s = k;
        i = v;
    };

    ASSERT_TRUE(meta::find(map, "salut", l));
    ASSERT_EQ(s, "salut");
    ASSERT_EQ(i, 0);

    ASSERT_TRUE(meta::find(map, "lolol", l));
    ASSERT_EQ(s, "lolol");
    ASSERT_EQ(i, 1);

    ASSERT_TRUE(meta::find(map, "tralala", l));
    ASSERT_EQ(s, "tralala");
    ASSERT_EQ(i, 2);

    ASSERT_FALSE(meta::find(map, "lul", l));

    std::vector<std::string> kVec;
    std::vector<int> vVec;

    meta::for_each(map, [&kVec, &vVec](auto &&k, auto &&v) {
        kVec.emplace_back(k);
        vVec.emplace_back(v);
    });
    ASSERT_EQ(kVec.size(), 3u);
    ASSERT_EQ(kVec[0], "salut");
    ASSERT_EQ(kVec[1], "lolol");
    ASSERT_EQ(kVec[2], "tralala");

    ASSERT_EQ(vVec.size(), 3u);
    ASSERT_EQ(vVec[0], 0);
    ASSERT_EQ(vVec[1], 1);
    ASSERT_EQ(vVec[2], 2);
}
