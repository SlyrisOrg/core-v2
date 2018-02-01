//
// Created by doom on 01/02/18.
//

#include <string>
#include <gtest/gtest.h>
#include <core/utils/Guard.hpp>

TEST(Guard, BasicCleanup)
{
    bool called = false;
    auto cleanupFunc = [&called](int) {
        called = true;
    };

    {
        utils::Guard<int> i(2, cleanupFunc);
    }
    ASSERT_TRUE(called);
}

TEST(Guard, Get)
{
    auto cleanupFunc = [](std::string arr[]) {
        ASSERT_EQ(arr[0], "lala");
        delete[] arr;
    };
    utils::Guard < std::string * > strArray(new std::string[4], cleanupFunc);
    strArray.get()[0] = "lala";
}

namespace
{
    struct Lol
    {
        int lala;
    };
}

TEST(Guard, Dereference)
{

    auto onCleanup = [](Lol &) {
    };

    utils::Guard <Lol> l({1}, onCleanup);
    ASSERT_EQ(l->lala, 1);
    l->lala = 2;
    ASSERT_EQ(l->lala, 2);
}
