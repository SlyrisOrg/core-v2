//
// Created by doom on 01/02/18
//

#include <type_traits>
#include <gtest/gtest.h>
#include <core/utils/NonCopyable.hpp>
#include <core/utils/NonMovable.hpp>
#include <core/utils/NamedType.hpp>

namespace
{
    class DummyCopyable
    {
    };

    class DummyNonCopyable : utils::NonCopyable
    {
    };
}

TEST(Utils, NonCopyable)
{
    ASSERT_TRUE(std::is_copy_constructible_v<DummyCopyable>);
    ASSERT_FALSE(std::is_copy_constructible_v<DummyNonCopyable>);
    ASSERT_TRUE(std::is_copy_assignable_v<DummyCopyable>);
    ASSERT_FALSE(std::is_copy_assignable_v<DummyNonCopyable>);
}

namespace
{
    class DummyMovable
    {
    };

    class DummyNonMovable : utils::NonMovable
    {
    };
}

TEST(Utils, NonMovable)
{
    ASSERT_TRUE(std::is_move_constructible_v<DummyMovable>);
    ASSERT_FALSE(std::is_move_constructible_v<DummyNonMovable>);
    ASSERT_TRUE(std::is_move_assignable_v<DummyMovable>);
    ASSERT_FALSE(std::is_move_assignable_v<DummyNonMovable>);
}

using XCoord = utils::NamedType<double, struct XTag>;
using YCoord = utils::NamedType<double, struct YTag>;
using Name = utils::NamedType<std::string, struct NameTag>;

TEST(Utils, NamedType)
{
    ASSERT_FALSE((std::is_convertible_v<XCoord, double>));
    ASSERT_FALSE((std::is_convertible_v<XCoord, double>));
    ASSERT_FALSE((std::is_convertible_v<Name, std::string>));

    XCoord x = 2.3;
    YCoord y = 3.2;
    Name name = std::string("Lalala");
    ASSERT_EQ(x.get(), 2.3);
    ASSERT_EQ(y.get(), 3.2);
    ASSERT_EQ(name.get(), "Lalala");
}
