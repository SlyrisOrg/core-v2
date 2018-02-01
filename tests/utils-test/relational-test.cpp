//
// Created by doom on 01/02/18.
//

#include <gtest/gtest.h>
#include <core/utils/Relational.hpp>

class Integer : public utils::Relational<Integer>
{
public:
    Integer(int value) noexcept : _value(value)
    {
    }

    bool operator<(const Integer &other) const noexcept
    {
        return _value < other._value;
    }

    bool operator==(const Integer &other) const noexcept
    {
        return _value == other._value;
    }

private:
    int _value;
};

TEST(Relational, Basic)
{
    Integer a(2);
    Integer b(3);

    ASSERT_LE(a, b);
    ASSERT_LT(a, b);

    ASSERT_GE(b, a);
    ASSERT_GT(b, a);

    ASSERT_NE(a, b);
}

TEST(Relational, Equal)
{
    Integer a(2);
    Integer b(2);

    ASSERT_LE(a, b);
    ASSERT_LE(b, a);

    ASSERT_GE(a, b);
    ASSERT_GE(b, a);

    ASSERT_FALSE(a < b);
    ASSERT_FALSE(b < a);
    ASSERT_FALSE(a > b);
    ASSERT_FALSE(b > a);

    ASSERT_EQ(a, b);
}
