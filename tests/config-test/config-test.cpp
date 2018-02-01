//
// Created by doom on 31/01/18.
//

#include <gtest/gtest.h>
#include <core/config/Config.hpp>

TEST(Config, Features)
{
    bool hasPlatform = false;

#if defined(USING_LINUX) || defined(USING_OSX) || defined(USING_WINDOWS)
    hasPlatform = true;
#endif

    ASSERT_TRUE(hasPlatform);
}

TEST(Config, CompilerFeatures)
{
    bool has__FUNCTION__ = false;
    bool hasEXPORT_SYMBOL = false;

#if defined(__FUNCTION__)
    has__FUNCTION__ = true;
#endif

#if defined(EXPORT_SYMBOL)
    hasEXPORT_SYMBOL = true;
#endif

    ASSERT_TRUE(has__FUNCTION__);
    ASSERT_TRUE(hasEXPORT_SYMBOL);
    ASSERT_TRUE(likely(true));
    ASSERT_FALSE(likely(false));
    ASSERT_TRUE(unlikely(true));
    ASSERT_FALSE(unlikely(false));
}