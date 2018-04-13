//
// Created by sidne on 12/04/2018.
//
// Define macros and functions based on compilers specific instructions :
//   - always_inline and no_inline function specifiers
//   - likely and unlikely specifiers for branch prediction
//   - export_symbol, import_symbol and local_symbol for shared or dynamic libraries
//   - unreachable function to mark a path as unreachable
//

#ifndef CORE_COMPILERHINTS_HPP
#define CORE_COMPILERHINTS_HPP

#include "Environment.hpp"
#include <cstdlib>

// define always_inline and no_inline

#if   defined(USING_MSVC)
    #define always_inline __forceinline
    #define no_inline     __declspec(noinline)
#elif defined(USING_CLANG) || defined(USING_GCC)
    #define always_inline __attribute__((always_inline)) inline
    #define no_inline     __attribute__((noinline))
#else
    #define always_inline inline
    #define no_inline
#endif

// define likely and unlikely

#if defined(USING_CLANG) || defined(USING_GCC)
    #define likely(x)   (__builtin_expect(static_cast<bool>(x), true))
    #define unlikely(x) (__builtin_expect(static_cast<bool>(x), false))
#else
    #define likely(x)   (static_cast<bool>(x))
    #define unlikely(x) (static_cast<bool>(x))
#endif

// define export_symbol, import_symbol and local_symbol

#if defined(USING_MSVC)
    #define export_symbol __declspec(dllexport)
    #define import_symbol __declspec(dllimport)
    #define local_symbol
#elif defined(USING_CLANG) || defined(USING_GCC)
    #define export_symbol __attribute__((visibility("default")))
    #define import_symbol
    #define local_symbol  __attribute__((visibility("hidden")))
#else
    #define export_symbol
    #define import_symbol
    #define local_symbol
#endif

// define unreachable

#if defined(UNKNOWN_COMPILER) || defined(DEBUG_BUILD)
    [[noreturn]] void always_inline unreachable() noexcept {
        std::abort();
    }
#elif defined(USING_WINDOWS)
    [[noreturn]] void always_inline unreachable() noexcept {
        __assume(false);
    }
#else
    [[noreturn]] void always_inline unreachable() noexcept {
        __builtin_unreachable();
    }
#endif

// define __PRETTY_FUNCTION__ where it doesn't exists

#if !defined(__PRETTY_FUNCTION__)
    #if defined(USING_MSVC)
        #define __PRETTY_FUNCTION__ __FUNCSIG__
    #else
        #define __PRETTY_FUNCTION__ __func__
    #endif
#endif


#endif //CORE_COMPILERHINTS_HPP
