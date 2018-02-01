//
// Created by doom on 01/02/18.
//

#include <gtest/gtest.h>
#include <core/utils/LexicalCast.hpp>

TEST(LexicalCast, ToString)
{
    ASSERT_EQ(utils::lexicalCast<std::string>(0), "0");
    ASSERT_EQ(utils::lexicalCast<std::string>(1), "1");
    ASSERT_EQ(utils::lexicalCast<std::string>(3.14f), "3.14");
    ASSERT_EQ(utils::lexicalCast<std::string>(123456789), "123456789");
    ASSERT_EQ(utils::lexicalCast<std::string>(999999999999), "999999999999");
}

TEST(LexicalCast, FromString)
{
    ASSERT_EQ(utils::lexicalCast<int>("0"), 0);
    ASSERT_EQ(utils::lexicalCast<int>("1"), 1);
    ASSERT_EQ(utils::lexicalCast<float>("3.14"), 3.14f);
    ASSERT_THROW(utils::lexicalCast<int>("lalala"), utils::BadLexicalCast);
    ASSERT_EQ(utils::lexicalCast<int>("123456789"), 123456789);
    ASSERT_THROW(utils::lexicalCast<int>("999999999999"), utils::BadLexicalCast);
}

TEST(LexicalCast, Other)
{
    ASSERT_EQ(utils::lexicalCast<int>(0.f), 0);
    ASSERT_EQ(utils::lexicalCast<float>(0), 0.f);
}
