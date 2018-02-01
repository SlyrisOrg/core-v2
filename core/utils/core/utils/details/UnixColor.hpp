//
// Created by roman sztergbaum on 10/09/2017.
//

#ifndef CORE_UTILS_DETAILS_UNIX_COLOR_HPP
#define CORE_UTILS_DETAILS_UNIX_COLOR_HPP

#include <iostream>
#include <core/utils/ColorEnum.hpp>

namespace utils::details
{
    static constexpr const char *ansiAttributeReset = "\033[0m";
    static constexpr const char *ansiBlack = "\033[22;30m";
    static constexpr const char *ansiRed = "\033[22;31m";
    static constexpr const char *ansiGreen = "\033[22;32m";
    static constexpr const char *ansiBrown = "\033[22;33m";
    static constexpr const char *ansiBlue = "\033[22;34m";
    static constexpr const char *ansiMagenta = "\033[22;35m";
    static constexpr const char *ansiCyan = "\033[22;36m";
    static constexpr const char *ansiGrey = "\033[22;37m";
    static constexpr const char *ansiDarkGrey = "\033[01;30m";
    static constexpr const char *ansiBrightRed = "\033[01;31m";
    static constexpr const char *ansiBrightGreen = "\033[01;32m";
    static constexpr const char *ansiBrightYellow = "\033[01;33m";
    static constexpr const char *ansiBrightBlue = "\033[01;34m";
    static constexpr const char *ansiLightMagenta = "\033[01;35m";
    static constexpr const char *ansiLightCyan = "\033[01;36m";
    static constexpr const char *ansiWhite = "\033[01;37m";
    static constexpr const char *ansiBackgroundBlack = "\033[40m";
    static constexpr const char *ansiBackgroundRed = "\033[41m";
    static constexpr const char *ansiBackgroundGreen = "\033[42m";
    static constexpr const char *ansiBackgroundYellow = "\033[43m";
    static constexpr const char *ansiBackgroundBlue = "\033[44m";
    static constexpr const char *ansiBackgroundMagenta = "\033[45m";
    static constexpr const char *ansiBackgroundCyan = "\033[46m";
    static constexpr const char *ansiBackgroundWhite = "\033[47m";

    inline const char *getAnsiColor(utils::Color c) noexcept
    {
        switch (c) {
            case Black:
                return ansiBlack;
            case Blue:
                return ansiBlue;
            case Green:
                return ansiGreen;
            case Cyan:
                return ansiCyan;
            case Red:
                return ansiRed;
            case Magenta:
                return ansiMagenta;
            case Brown:
                return ansiBrown;
            case Grey:
                return ansiGrey;
            case DarkGrey:
                return ansiDarkGrey;
            case LightBlue:
                return ansiBrightBlue;
            case LightGreen:
                return ansiBrightGreen;
            case LightCyan:
                return ansiLightCyan;
            case LightRed:
                return ansiBrightRed;
            case LightMagenta:
                return ansiLightMagenta;
            case Yellow:
                return ansiBrightYellow;
            case White:
                return ansiWhite;
            default:
                return "";
        }
    }

    inline const char *getAnsiBackgroundColor(utils::Color c) noexcept
    {
        switch (c) {
            case Black:
                return ansiBackgroundBlack;
            case Blue:
                return ansiBackgroundBlue;
            case Green:
                return ansiBackgroundGreen;
            case Cyan:
                return ansiBackgroundCyan;
            case Red:
                return ansiBackgroundRed;
            case Magenta:
                return ansiBackgroundMagenta;
            case Brown:
                return ansiBackgroundYellow;
            case Grey:
                return ansiBackgroundWhite;
            default:
                return "";
        }
    }

    static inline void setColor(utils::Color c) noexcept
    {
        std::cout << getAnsiColor(c);
    }

    static inline void setBackgroundColor(utils::Color c) noexcept
    {
        std::cout << getAnsiBackgroundColor(c);
    }

    static inline void resetColor() noexcept
    {
        std::cout << ansiAttributeReset;
    }

    static inline void saveDefaultColor() noexcept
    {
        return;
    }

    static inline void setColor(Color color, std::ostream &ostream) noexcept
    {
        ostream << getAnsiColor(color);
    }
}

#endif //CORE_UTILS_DETAILS_UNIX_COLOR_HPP
