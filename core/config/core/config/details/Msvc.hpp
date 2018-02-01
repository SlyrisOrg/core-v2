//
// Created by szterg_r on 22/08/2017.
//

#ifndef CORE_CONFIG_DETAILS_MSVC_HPP
#define CORE_CONFIG_DETAILS_MSVC_HPP

#define USING_MSVC

#define EXPORT_SYMBOL   __declspec(dllexport)

#define always_inline   __forceinline

static always_inline constexpr bool likely(bool x) noexcept
{
    return x;
}

static always_inline constexpr bool unlikely(bool x) noexcept
{
    return x;
}

#endif //CORE_CONFIG_DETAILS_MSVC_HPP
