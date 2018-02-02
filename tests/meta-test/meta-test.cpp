//
// Created by doom on 01/02/18
//

#include <gtest/gtest.h>
#include <meta/Meta.hpp>
#include <functional>


class ILikeReflection
{
public:
    ILikeReflection(int i, const std::string &s, double d) noexcept : _i(i), _s(s), _d(d)
    {
    }

private:
    int _i;
    std::string _s;
    double _d;

public:
    static constexpr auto memberMap() noexcept
    {
        return meta::makeMap(
            reflect_member(&ILikeReflection::_i),
            reflect_member(&ILikeReflection::_s),
            reflect_member(&ILikeReflection::_d)
        );
    }
};

class IDontLikeReflection
{
};

TEST(Meta, Reflection)
{
    using namespace std::literals;
    ASSERT_TRUE(meta::is_reflectible_v<ILikeReflection>);
    ASSERT_FALSE(meta::is_reflectible_v<IDontLikeReflection>);

    //Dummy values to ensure initialization
    int i = -1;
    std::string s;
    double d = -1.;

    ILikeReflection ilr{1, "salut", 3.2};

    auto visitor = meta::makeVisitor([&i, &ilr](auto &&, int ILikeReflection::* iPtr) {
        i = ilr.*iPtr;
    }, [&s, &ilr](auto &&, std::string ILikeReflection::* sPtr) {
        s = ilr.*sPtr;
    }, [&d, &ilr](auto &&, double ILikeReflection::* dPtr) {
        d = ilr.*dPtr;
    });

    meta::for_each(ILikeReflection::memberMap(), visitor);
    ASSERT_EQ(i, 1);
    ASSERT_EQ(s, "salut");
    ASSERT_EQ(d, 3.2);

    i = -1;
    s.clear();
    d = -1.;

    get_reflected_member(ILikeReflection::memberMap(), "_i"sv, visitor);
    get_reflected_member(ILikeReflection::memberMap(), "_s"sv, visitor);
    get_reflected_member(ILikeReflection::memberMap(), "_d"sv, visitor);
    ASSERT_EQ(i, 1);
    ASSERT_EQ(s, "salut");
    ASSERT_EQ(d, 3.2);
}

struct IHaveAReflectiveName
{
    reflect_class(IHaveAReflectiveName);
};

struct IHaveAReflecibleMemFunc
{
    int func(int i)
    {
        return i;
    }

    static constexpr auto memberMap() noexcept
    {
        return meta::makeMap(reflect_member(&IHaveAReflecibleMemFunc::func));
    }
};

TEST(Meta, Reflection2)
{
    using namespace std::literals;
    ASSERT_EQ(IHaveAReflectiveName::className(), "IHaveAReflectiveName");

    int i = 0;

    get_reflected_function(IHaveAReflecibleMemFunc::memberMap(), "func"sv, ([&i](auto &&, auto &&v) {
        IHaveAReflecibleMemFunc iharmf;
        i = std::invoke(v, iharmf, 1);
    }));
    ASSERT_EQ(i, 1);
}
