//
// Created by doom on 11/10/17.
//

#ifndef CORE_LIB_EXCEPTIONS_HPP
#define CORE_LIB_EXCEPTIONS_HPP

#include <string>
#include <exception>

namespace lib
{
    class LibraryNotLoaded : public std::exception
    {
    public:
        const char *what() const noexcept
        {
            return "Unable to load symbols from an unloaded library";
        }
    };

    class SymbolNotFound : public std::exception
    {
    public:
        SymbolNotFound(const std::string &reason) noexcept : _message("Symbol not found in shared library: " + reason)
        {
        }

        const char *what() const noexcept
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };
}

#endif //CORE_LIB_EXCEPTIONS_HPP
