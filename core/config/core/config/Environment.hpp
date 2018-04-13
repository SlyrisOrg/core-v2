//
// Created by sidney on 12/04/2018.
//
// Detect environment properties at compile-time :
//   - endian type
//   - platform (os)
//   - compiler
//   - debug or release mode
//

#ifndef CORE_CONFIG_ENVIRONMENT_HPP
#define CORE_CONFIG_ENVIRONMENT_HPP

#include <cstdint>

namespace config {

    // Detect little or big endian

    namespace detail {
        constexpr bool hasLittleEndian() noexcept
        {
            constexpr uint32_t num = 0xAABBCCDD;
            constexpr uint8_t firstByte = (const uint8_t &)(num);
            return firstByte == 0xDD;
        }

        constexpr bool hasBigEndian() noexcept
        {
            constexpr uint32_t num = 0xAABBCCDD;
            constexpr uint8_t firstByte = (const uint8_t &)(num);
            return firstByte == 0xAA;
        }
    }
    namespace endian {
        enum type {
            big,
            little,
        };
    };
    constexpr endian::type current_endian = detail::hasBigEndian() ? endian::big : endian::little;

    // Detect platform (+ remove obsolete macro 'linux')

    #if defined(linux)
        #undef linux
    #endif

    namespace os {
        enum type {
            windows,
            apple,
            linux,
            unknown,
        };
    }
    #if   defined(_WIN32)
        #define USING_WINDOWS
        constexpr os::type current_os = os::windows;
    #elif defined(__APPLE__)
        #define USING_APPLE
        #define USING_UNIX
        constexpr os::type current_os = os::apple;
    #elif defined(__linux__)
        #define USING_LINUX
        #define USING_UNIX
        constexpr os::type current_os = os::linux;
    #else
        #define USING_UNKNOWN_OS
        constexpr os::type current_os = os::unknown;
    #endif

    // Detect compiler

    namespace compiler {
        enum type {
            gcc,
            clang,
            msvc,
            unknown,
        };
    }
    #if   defined(__clang__)
        #define USING_CLANG
        constexpr compiler::type current_compiler = compiler::clang;
    #elif defined(__GNUC__)
        #define USING_GCC
        constexpr compiler::type current_compiler = compiler::gcc;
    #elif defined(_MSC_VER)
        #define USING_MSVC
        constexpr compiler::type current_compiler = compiler::msvc;
    #else
        #define USING_UNKNOWN_COMPILER
        constexpr compiler::type current_compiler = compiler::unknown;
    #endif

    // Detect release or debug mode

    namespace mode {
        enum type {
            debug,
            release,
        };
    }
    #if defined(NDEBUG)
        #define RELEASE_BUILD
        constexpr mode::type current_mode = mode::release;
    #else
        #define DEBUG_BUILD
        constexpr mode::type current_mode = mode::debug;
    #endif

}

#endif //CORE_CONFIG_ENVIRONMENT_HPP
