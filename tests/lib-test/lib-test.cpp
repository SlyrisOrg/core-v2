//
// Created by doom on 02/02/18
//

#include <gtest/gtest.h>
#include <core/lib/Lib.hpp>
#include "test/ITest.hpp"
#include "test2/ITest2.hpp"

TEST(Lib, Basic)
{
    lib::SharedLibrary lib;

    lib.load(fs::path("lollib"), lib::LoadingMode::Default);
    ASSERT_TRUE(lib.isLoaded());

    auto double_this = lib.get<int(int)>("double_this");
    ASSERT_EQ(double_this(2), 4);

    auto a_number = lib.get<int>("a_number");
    ASSERT_EQ(a_number, 42);

    lib.unload();
    ASSERT_FALSE(lib.isLoaded());
}

TEST(Lib, LoadClass)
{
    auto testAlias = lib::getSymbol<ITest>(fs::path("testlib"), "testInstance", lib::LoadingMode::Default);

    ASSERT_EQ(testAlias->add(3, 4), 7);

    auto testAlias2 = lib::getSymbol<ITest>(fs::path("testlib"), "testInstance", lib::LoadingMode::Default);

    ASSERT_EQ(testAlias2->add(437, 4), 441);

    ASSERT_EQ(testAlias->getLastResult(), 441);
}

TEST(Lib, NotLoaded)
{
    lib::SharedLibrary lib;

    ASSERT_THROW(lib.get<int(int)>("my_is_prime"), lib::LibraryNotLoaded);
}

TEST(Lib, InexistentSymbols)
{
    lib::SharedLibrary lib(fs::path("lollib"), lib::LoadingMode::Default);
    ASSERT_TRUE(lib.isLoaded());

    ASSERT_FALSE(lib.hasSymbol("inexistent_symbol"));
    ASSERT_THROW(lib.get<int>("inexistent_symbol"), lib::SymbolNotFound);
}

TEST(Lib, Alias)
{
    auto create = lib::getSymbol<ITest2 *(*)()>(fs::path("test2lib"), "create", lib::LoadingMode::Default);
    auto testAlias = (*create)();

    ASSERT_EQ(testAlias->add(3, 4), 7);

    auto testAlias2 = (*create)();

    ASSERT_EQ(testAlias2->add(437, 4), 441);

    ASSERT_EQ(testAlias->getLastResult(), 7);

    delete testAlias;
    delete testAlias2;
}
