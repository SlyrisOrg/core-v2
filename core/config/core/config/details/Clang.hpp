//
// Created by szterg_r on 22/08/2017.
//

#ifndef CORE_UTILS_CLANG_HPP
#define CORE_UTILS_CLANG_HPP

#define USING_CLANG

#define EXPORT_SYMBOL

#define always_inline   __attribute__((always_inline)) inline

#define __FUNCTION__    __PRETTY_FUNCTION__

static always_inline constexpr bool likely(bool x) noexcept
{
    return __builtin_expect(x, true);
}

static always_inline constexpr bool unlikely(bool x) noexcept
{
    return __builtin_expect(x, false);
}

#endif //CORE_UTILS_CLANG_HPP
