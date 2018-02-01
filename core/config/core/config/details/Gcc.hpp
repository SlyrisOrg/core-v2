//
// Created by szterg_r on 22/08/2017.
//

#ifndef CORE_CONFIG_DETAILS_GCC_HPP
#define CORE_CONFIG_DETAILS_GCC_HPP

#define USING_GCC

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

#endif //CORE_CONFIG_DETAILS_GCC_HPP
