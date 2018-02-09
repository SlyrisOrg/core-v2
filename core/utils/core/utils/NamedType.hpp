//
// Created by doom on 09/02/18.
//

#ifndef CORE_UTILS_NAMEDTYPE_HPP
#define CORE_UTILS_NAMEDTYPE_HPP

#include <utility>

namespace utils
{
    template <typename T, typename Tag>
    class NamedType
    {
    public:
        NamedType(const T &t) : _t(t)
        {
        }

        NamedType(T &&t) noexcept : _t(std::move(t))
        {
        }

        T &get() noexcept
        {
            return _t;
        }

        const T &get() const noexcept
        {
            return _t;
        }

    private:
        T _t;
    };
}

#endif //CORE_UTILS_NAMEDTYPE_HPP
