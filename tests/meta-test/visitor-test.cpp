//
// Created by doom on 01/02/18.
//

#include <string>
#include <gtest/gtest.h>
#include <core/meta/Visitor.hpp>

TEST(Meta, Visitor)
{
    unsigned int idx;

    auto chooser = meta::makeVisitor([&idx](unsigned int) {
        idx = 0;
    }, [&idx](const std::string &) {
        idx = 1;
    }, [&idx](int) {
        idx = 2;
    });

    chooser(2u);
    ASSERT_EQ(idx, 0u);

    chooser("lala");
    ASSERT_EQ(idx, 1u);

    chooser(-2);
    ASSERT_EQ(idx, 2u);
}
