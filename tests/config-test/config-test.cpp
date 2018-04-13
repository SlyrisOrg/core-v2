//
// Created by doom on 31/01/18.
//

#include <gtest/gtest.h>
#include <core/config/CompilerHints.hpp>
#include <numeric>

namespace {

    // Check that there is no warning or error at compilation because all paths doesn't return a value
    int switch_on(int count) {
        switch (count) {
            case 1: return 0;
            case 2: return 1;
            case 5: return 2;
            case 10: return 3;
            default: unreachable();
        }
    }

    // SO & DLL symbols
    export_symbol void exported_function();
    import_symbol void imported_function();
    local_symbol  void local_function();

    // Make sure the function is inlined due to alloca behavior
    // On Windows, the function isn't inlined in debug mode (leading to corrupt stack memory). Use /Ob1+
    template <class T>
    always_inline T* make_array(int size) {
        auto ptr = static_cast<T*>(alloca(size * sizeof(T)));
        for (int i = 0; i < size; ++i) {
            new (ptr + i) T();
        }
        return ptr;
    }

}

TEST(Config, Environment)
{
    using namespace config;

    bool knowEndian = false;
    if constexpr (current_endian == endian::little || endian::big) {
        knowEndian = true;
    }
    ASSERT_TRUE(knowEndian);

    bool knownPlatform = false;
    if constexpr (current_os == os::windows || os::linux || os::apple) {
        knownPlatform = true;
    }
    ASSERT_TRUE(knownPlatform);

    bool knownCompiler = false;
    if constexpr (current_compiler == compiler::msvc || compiler::gcc || compiler::clang) {
        knownCompiler = true;
    }
    ASSERT_TRUE(knownCompiler);

    bool knownMode = false;
    if constexpr (current_mode == mode::debug || mode::release) {
        knownMode = true;
    }
    ASSERT_TRUE(knownMode);
}

TEST(Config, CompilerHints)
{
    ASSERT_TRUE(switch_on(5) == 2);

    // Common error handling setup
    if unlikely (true) {
        []() no_inline {
            SUCCEED();
        }();
    }
    else {
        FAIL();
    }

    ASSERT_TRUE (likely  (true));
    ASSERT_FALSE(likely  (false));
    ASSERT_TRUE (unlikely(true));
    ASSERT_FALSE(unlikely(false));
}