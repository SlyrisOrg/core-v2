//
// Created by doom on 04/02/18
//

#include <vector>
#include <gtest/gtest.h>
#include <core/containers/Span.hpp>

TEST(Span, Construction)
{
    int arr[] = {1, 2, 3, 4, 5, 6};

    //1st constructor
    ctr::Span<int> s1;
    ASSERT_EQ(s1.size(), 0u);

    //2nd constructor
    ctr::Span<int> s2(&arr[1], 5);
    ASSERT_EQ(s2.size(), 5u);
    for (size_t i = 0; i < s2.size(); ++i) {
        ASSERT_EQ(s2[i], arr[i + 1]);
    }

    //3rd constructor
    ctr::Span<int> s3(&arr[0], &arr[4]);
    ASSERT_EQ(s3.size(), 4u);
    for (size_t i = 0; i < s3.size(); ++i) {
        ASSERT_EQ(s3[i], arr[i]);
    }

    //4th constructor
    ctr::Span<int> s4(arr);
    ASSERT_EQ(s4.size(), 6u);
    for (size_t i = 0; i < s2.size(); ++i) {
        ASSERT_EQ(s4[i], arr[i]);
    }

    //7th constructor
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    ctr::Span<int> s5(vec);
    ASSERT_EQ(s5.size(), 6u);
    for (size_t i = 0; i < s5.size(); ++i) {
        ASSERT_EQ(s5[i], arr[i]);
    }

    //8th constructor
    ctr::Span<int> s6(vec.begin(), vec.begin() + 4);
    ASSERT_EQ(s6.size(), 4u);
    for (size_t i = 0; i < s6.size(); ++i) {
        ASSERT_EQ(s6[i], arr[i]);
    }

    ASSERT_EQ(s4, s5);
    ASSERT_NE(s5, s6);
}

TEST(Span, SubSpan)
{
    int arr[] = {1, 2, 3, 4, 5, 6};

    ctr::Span<int> sp(arr);

    auto sub1 = sp.subspan(0, 5);
    ASSERT_EQ(sub1.size(), 5u);
    for (size_t i = 0; i < sub1.size(); ++i) {
        ASSERT_EQ(sub1[i], sp[i]);
    }

    auto sub2 = sub1.subspan(1, 2);
    ASSERT_EQ(sub2.size(), 2u);
    for (size_t i = 0; i < sub2.size(); ++i) {
        ASSERT_EQ(sub2[i], sub1[i + 1]);
        ASSERT_EQ(sub2[i], sp[i + 1]);
    }
}

TEST(Span, BasicIteration)
{
    int arr[] = {1, 2, 3, 4, 5, 6};

    const ctr::Span<int> sp(arr);

    size_t i = 0;
    for (auto it = sp.begin(); it != sp.end(); ++it) {
        ASSERT_EQ(*it, arr[i]);
        ++i;
    }

    i = sp.size() - 1;
    for (auto it = sp.rbegin(); it != sp.rend(); ++it) {
        ASSERT_EQ(*it, arr[i]);
        --i;
    }

    i = 0;
    for (const auto &cur : sp) {
        ASSERT_EQ(cur, arr[i]);
        ++i;
    }

    i = 0;
    for (auto &cur : sp) {
        ASSERT_EQ(cur, arr[i]);
        ++i;
    }
}

TEST(Span, InputIteration)
{
    int arr[] = {1, 2, 3, 4, 5, 6};

    const ctr::Span<int> sp(&arr[2], 3);
    std::vector<int> vec{sp.begin(), sp.end()};
    ASSERT_EQ(vec.size(), 3u);
    ASSERT_EQ(vec[0], arr[2]);
    ASSERT_EQ(vec[1], arr[3]);
    ASSERT_EQ(vec[2], arr[4]);

    const ctr::Span<int> sp2(arr);
    std::vector<int> vec2{sp2.begin() + 3, sp2.end()};
    ASSERT_EQ(vec2.size(), 3u);
    ASSERT_EQ(vec2[0], arr[3]);
    ASSERT_EQ(vec2[1], arr[4]);
    ASSERT_EQ(vec2[2], arr[5]);
}
