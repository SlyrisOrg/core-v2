//
// Created by doom on 02/02/18
//

#include <functional>
#include <gtest/gtest.h>
#include <core/meta/Visitor.hpp>
#include <core/reflection/Reflection.hpp>

namespace
{
    class IDontLikeRefl
    {
    };

    class ILikeRefl
    {
    public:
        ILikeRefl(int i, const std::string &s, double d) noexcept : _i(i), _s(s), _d(d)
        {
        }

    private:
        int _i;
        std::string _s;
        double _d;

    public:
        static constexpr auto reflectedMembers() noexcept
        {
            return meta::makeMap(
                reflect_member(&ILikeRefl::_i),
                reflect_member(&ILikeRefl::_s),
                reflect_member(&ILikeRefl::_d)
            );
        }
    };

    struct IHaveAReflectibleName
    {
        reflect_class(IHaveAReflectibleName);
    };

    struct IHaveAReflMemFunc
    {
        int func(int i)
        {
            return i;
        }

        static constexpr auto reflectedFunctions() noexcept
        {
            return meta::makeMap(reflect_function(&IHaveAReflMemFunc::func));
        }
    };
}

TEST(Reflection, Traits)
{
    ASSERT_TRUE(refl::has_reflectible_members_v<ILikeRefl>);
    ASSERT_FALSE(refl::has_reflectible_functions_v<ILikeRefl>);

    ASSERT_TRUE(refl::has_reflectible_functions_v<IHaveAReflMemFunc>);
    ASSERT_FALSE(refl::has_reflectible_members_v<IHaveAReflMemFunc>);

    ASSERT_TRUE(refl::is_reflectible_v<ILikeRefl>);
    ASSERT_TRUE(refl::is_reflectible_v<IHaveAReflMemFunc>);
    ASSERT_FALSE(refl::is_reflectible_v<IDontLikeRefl>);

    ASSERT_TRUE(refl::has_reflectible_class_name_v<IHaveAReflectibleName>);
    ASSERT_FALSE(refl::has_reflectible_class_name_v<ILikeRefl>);
    ASSERT_FALSE(refl::has_reflectible_class_name_v<IHaveAReflMemFunc>);
}

TEST(Reflection, Members)
{
    using namespace std::literals;

    //Dummy values to ensure initialization
    int i = -1;
    std::string s;
    double d = -1.;

    ILikeRefl ilr{1, "salut", 3.2};

    auto visitor = meta::makeVisitor([&i, &ilr](auto &&, int ILikeRefl::* iPtr) {
        i = ilr.*iPtr;
    }, [&s, &ilr](auto &&, std::string ILikeRefl::* sPtr) {
        s = ilr.*sPtr;
    }, [&d, &ilr](auto &&, double ILikeRefl::* dPtr) {
        d = ilr.*dPtr;
    });

    meta::for_each(ILikeRefl::reflectedMembers(), visitor);
    ASSERT_EQ(i, 1);
    ASSERT_EQ(s, "salut");
    ASSERT_EQ(d, 3.2);

    i = -1;
    s.clear();

    refl::getMember(ILikeRefl::reflectedMembers(), "_i"sv, visitor);
    refl::getMember(ILikeRefl::reflectedMembers(), "_s"sv, visitor);
    auto dPtrOpt = refl::getMember<double ILikeRefl::*>(ILikeRefl::reflectedMembers(), "_d"sv);
    auto emptyOpt = refl::getMember<char ILikeRefl::*>(ILikeRefl::reflectedMembers(), "_c"sv);

    ASSERT_EQ(i, 1);
    ASSERT_EQ(s, "salut");
    ASSERT_TRUE(dPtrOpt);
    auto dPtr = *dPtrOpt;
    ASSERT_EQ(ilr.*dPtr, 3.2);
    ASSERT_FALSE(emptyOpt);
}

TEST(Reflection, MemberFunctions)
{
    using namespace std::literals;

    int i = 0;

    refl::getFunction(IHaveAReflMemFunc::reflectedFunctions(), "func"sv, ([&i](auto &&, auto &&v) {
        IHaveAReflMemFunc iharmf;
        i = std::invoke(v, iharmf, 1);
    }));
    ASSERT_EQ(i, 1);

    IHaveAReflMemFunc iharf2;
    i = refl::callFunction<int(int)>(IHaveAReflMemFunc::reflectedFunctions(), "func", &iharf2, 2);
    ASSERT_EQ(i, 2);
}

TEST(Reflection, ClassName)
{
    ASSERT_EQ(IHaveAReflectibleName::className(), "IHaveAReflectibleName");
}
