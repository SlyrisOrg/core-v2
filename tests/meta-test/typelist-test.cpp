//
// Created by doom on 01/02/18.
//

#include <gtest/gtest.h>
#include <core/meta/List.hpp>

TEST(Meta, TypeList)
{
    using T1 = meta::TypeList<int, int, char>;
    using T2 = meta::TypeList<int, int, char>;

    ASSERT_TRUE((std::is_same_v<T1, T2>));
}

TEST(Meta, TypeListPushBack)
{
    using T0 = meta::TypeList<int, int, char>;
    using T1 = meta::TypeList<int, int, char, float, double>;
    using T2 = meta::list::PushBack<T0, float, double>;

    ASSERT_TRUE((std::is_same_v<T1, T2>));
}

TEST(Meta, TypeListPushFront)
{
    using T0 = meta::TypeList<int, int, char>;
    using T1 = meta::TypeList<float, double, int, int, char>;
    using T2 = meta::list::PushFront<T0, float, double>;

    ASSERT_TRUE((std::is_same_v<T1, T2>));
}

TEST(Meta, TypeListConcat)
{
    using T0 = meta::TypeList<int, int, char>;
    using T1 = meta::TypeList<float, double, int, int, char>;
    using ResultType = meta::list::Concat<T0, T1>;
    using ExpectedType = meta::TypeList<int, int, char, float, double, int, int, char>;

    ASSERT_TRUE((std::is_same_v<ResultType, ExpectedType>));
}

TEST(Meta, TypeListContains)
{
    using T0 = meta::TypeList<int, int, char>;

    bool result = meta::list::Contains<T0, int>();
    ASSERT_TRUE(result);

    result = meta::list::Contains<T0, char>();
    ASSERT_TRUE(result);

    result = meta::list::Contains<T0, double>();
    ASSERT_FALSE(result);
}

TEST(Meta, TypeListContainsList)
{
    using Types0 = meta::TypeList<int, int *, int, char *, bool, double, bool>;
    using Types1 = meta::TypeList<int, int *, char *, double, bool>;
    using Types2 = meta::TypeList<int, int, int>;

    bool result = meta::list::ContainsList<Types0, Types1>();
    ASSERT_TRUE(result);

    result = meta::list::ContainsList<Types0, Types2>();
    ASSERT_TRUE(result);
}

TEST(Meta, TypeListLength)
{
    using T0 = meta::TypeList<int, char, bool, double, size_t>;
    using T1 = meta::TypeList<int, char, bool, double, size_t, char, int, float>;
    using T2 = meta::TypeList<int>;

    ASSERT_EQ(meta::list::Length<T0>(), 5u);
    ASSERT_EQ(meta::list::Length<T1>(), 8u);
    ASSERT_EQ(meta::list::Length<T2>(), 1u);
}

TEST(Meta, TypeListPosition)
{
    using T0 = meta::TypeList<int, char, bool, double, size_t>;
    using T1 = meta::TypeList<int, char, bool, double, size_t, char, int, float>;
    using T2 = meta::TypeList<int>;

    size_t pos = meta::list::Position<T0, int>();
    ASSERT_EQ(pos, 0u);

    pos = meta::list::Position<T2, int>();
    ASSERT_EQ(pos, 0u);

    pos = meta::list::Position<T1, float>();
    ASSERT_EQ(pos, 7u);
}

TEST(Meta, TypeListAt)
{
    using Types = meta::TypeList<int, char, bool, double, size_t>;
    using ExpectedType = bool;
    using Result = meta::list::At<Types, 2>;

    ASSERT_TRUE((std::is_same_v<ExpectedType, Result>));

    using ExpectedType2 = int;
    using Result2 = meta::list::At<Types, 0>;

    ASSERT_TRUE((std::is_same_v<ExpectedType2, Result2>));
}

TEST(Meta, TypeListTransform)
{
    using Types = meta::TypeList<int, char, bool, double, size_t>;
    using Expected = meta::TypeList<int *, char *, bool *, double *, size_t *>;
    using Result = meta::list::Transform<Types, std::add_pointer_t>;

    ASSERT_TRUE((std::is_same_v<Expected, Result>));
}

TEST(Meta, TypeListConvert)
{
    using Types = meta::TypeList<int, char, bool, double, size_t>;
    using ExpectedTuple = std::tuple<int, char, bool, double, size_t>;
    using ResultTuple = meta::list::Convert<Types, std::tuple>;

    ASSERT_TRUE((std::is_same_v<ExpectedTuple, ResultTuple>));
}

TEST(Meta, TypeListUniq)
{
    using Types = meta::TypeList<int, int, int, char, bool, double, bool>;
    using ResultTypes = meta::list::Uniq<Types>;
    using ExpectedTypes = meta::TypeList<int, char, bool, double>;

    ASSERT_TRUE((std::is_same_v<ResultTypes, ExpectedTypes>));
}

TEST(Meta, TypeListFilter)
{
    using Types = meta::TypeList<int, int *, int, char *, bool, double, bool>;
    using ResultTypes = meta::list::Filter<Types, std::is_pointer>;
    using ExpectedTypes = meta::TypeList<int *, char *>;

    ASSERT_TRUE((std::is_same_v<ResultTypes, ExpectedTypes>));
}
