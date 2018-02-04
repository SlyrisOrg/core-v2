//
// Created by doom on 04/02/18.
//

#include <gtest/gtest.h>
#include <core/containers/RingBuffer.hpp>

TEST(RingBuffer, PushWithOverwrite)
{
    ctr::RingBuffer<int, true> rbuff(3);

    rbuff.push(1);
    rbuff.push(2);
    rbuff.push(3);

    ASSERT_EQ(rbuff[0], 1);
    ASSERT_EQ(rbuff[1], 2);
    ASSERT_EQ(rbuff[2], 3);

    ASSERT_TRUE(rbuff.push(4));
    ASSERT_TRUE(rbuff.push(5));

    ASSERT_EQ(rbuff[0], 3);
    ASSERT_EQ(rbuff[1], 4);
    ASSERT_EQ(rbuff[2], 5);
}

TEST(RingBuffer, PushWithoutOverwrite)
{
    ctr::RingBuffer<int> rbuff(3);

    rbuff.push(1);
    rbuff.push(2);
    rbuff.push(3);

    ASSERT_EQ(rbuff[0], 1);
    ASSERT_EQ(rbuff[1], 2);
    ASSERT_EQ(rbuff[2], 3);

    ASSERT_FALSE(rbuff.push(4));
}

TEST(RingBuffer, Pop)
{
    ctr::RingBuffer<int> rbuff(3);

    rbuff.push(1);
    rbuff.push(2);
    rbuff.push(3);

    ASSERT_EQ(rbuff[0], 1);
    ASSERT_EQ(rbuff[1], 2);
    ASSERT_EQ(rbuff[2], 3);

    rbuff.pop();

    ASSERT_EQ(rbuff[0], 2);
    ASSERT_EQ(rbuff.size(), 2u);
}

TEST(RingBuffer, Iteration)
{
    size_t size = 200;
    ctr::RingBuffer <size_t> rbuff(size);

    for (size_t i = 0; i < size; ++i) {
        rbuff.push(i);
    }

    size_t i = 0;
    for (const auto &it : rbuff) {
        ASSERT_EQ(it, i);
        i += 1;
    }
}

TEST(RingBuffer, Copy)
{
    ctr::RingBuffer<int> rbuff(3);

    rbuff.push(1);
    rbuff.push(2);

    ctr::RingBuffer<int> rbuff2(rbuff);

    ASSERT_EQ(rbuff.avail(), rbuff2.avail());
    ASSERT_EQ(rbuff.size(), rbuff2.size());
    ASSERT_EQ(rbuff[0], rbuff2[0]);
    ASSERT_EQ(rbuff[1], rbuff2[1]);
}

TEST(RingBuffer, Move)
{
    ctr::RingBuffer<int> rbuff(3);

    rbuff.push(1);
    rbuff.push(2);

    ctr::RingBuffer<int> rbuff2(std::move(rbuff));

    ASSERT_EQ(rbuff2.avail(), 1u);
    ASSERT_EQ(rbuff2.size(), 2u);
    ASSERT_EQ(rbuff2[0], 1);
    ASSERT_EQ(rbuff2[1], 2);
}

TEST(RingBuffer, Affect)
{
    ctr::RingBuffer<int> rbuff(3);

    rbuff.push(1);
    rbuff.push(2);

    ctr::RingBuffer<int> rbuff2(3);
    rbuff2 = std::move(rbuff);
    ASSERT_EQ(rbuff2.avail(), 1u);
    ASSERT_EQ(rbuff2.size(), 2u);
    ASSERT_EQ(rbuff2[0], 1);
    ASSERT_EQ(rbuff2[1], 2);

    ctr::RingBuffer<int> rbuff3(3);

    rbuff3.push(1);
    rbuff3.push(2);

    ctr::RingBuffer<int> rbuff4(3);
    rbuff4 = rbuff3;
    ASSERT_EQ(rbuff4.avail(), 1u);
    ASSERT_EQ(rbuff4.size(), 2u);
    ASSERT_EQ(rbuff4[0], 1);
    ASSERT_EQ(rbuff4[1], 2);
}
