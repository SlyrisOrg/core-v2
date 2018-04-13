//
// Created by roman sztergbaum on 10/09/2017.
//

#ifndef CORE_UTILS_COLOR_HPP
#define CORE_UTILS_COLOR_HPP

#include <iostream>
#include <core/config/CompilerHints.hpp>
#include <core/utils/ColorEnum.hpp>
#include <core/utils/details/Color.hpp>

namespace utils
{
    static always_inline void setColor(Color color, std::ostream &ostream) noexcept
    {
        utils::details::setColor(color, ostream);
    }

    static always_inline void setColor(utils::Color c) noexcept
    {
        utils::details::setColor(c);
    }

    static always_inline void resetColor() noexcept
    {
        utils::details::resetColor();
    }

    static always_inline void setBackgroundColor(utils::Color c) noexcept
    {
        utils::details::setBackgroundColor(c);
    }

    static always_inline std::ostream &operator<<(std::ostream &os, utils::Color c) noexcept
    {
        utils::setColor(c, os);
        return os;
    }

    static always_inline std::ostream &operator<<(std::ostream &os, [[maybe_unused]] utils::ResetColor c) noexcept
    {
#ifdef USING_WINDOWS
        utils::resetColor();
#elif defined(USING_UNIX)
        os << details::ansiAttributeReset;
#endif
        return os;
    }
}

#endif //CORE_UTILS_COLOR_HPP
