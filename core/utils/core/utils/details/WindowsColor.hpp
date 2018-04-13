//
// Created by roman sztergbaum on 10/09/2017.
//

#ifndef CORE_UTILS_DETAILS_WINDOWS_COLOR_HPP
#define CORE_UTILS_DETAILS_WINDOWS_COLOR_HPP

#include <iostream>
#include <core/config/CompilerHints.hpp>
#include <core/utils/ColorEnum.hpp>
#include <windows.h>

namespace utils::details
{
    static always_inline void setColor(utils::Color c) noexcept
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(hConsole, &csbi);
        SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c);
    }

    static always_inline void setColor(utils::Color c, std::ostream &stream) noexcept
    {
        HANDLE hConsole = INVALID_HANDLE_VALUE;
        if (&stream == &std::cerr)
            hConsole = GetStdHandle(STD_ERROR_HANDLE);
        else if (&stream == &std::cout)
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(hConsole, &csbi);
        SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c);
    }

    static always_inline void setBackgroundColor(utils::Color c) noexcept
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(hConsole, &csbi);

        SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFF0F) | (((WORD)c) << 4));
    }

    static always_inline int saveDefaultColor() noexcept
    {
        static bool initialized = false;
        static WORD attributes;

        if (!initialized) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &csbi);
            attributes = csbi.wAttributes;
            initialized = true;
        }
        return static_cast<int>(attributes);
    }

    static always_inline void resetColor() noexcept
    {
        setColor(utils::White, std::cout);
        setColor(utils::White, std::cerr);
    }
}

#endif //CORE_UTILS_DETAILS_WINDOWS_COLOR_HPP
