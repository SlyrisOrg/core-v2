//
// Created by milerius on 23/08/17.
//

#ifndef CORE_UTILS_RELATIONAL_HPP
#define CORE_UTILS_RELATIONAL_HPP

namespace utils
{
    template <typename T>
    struct Relational
    {
        friend bool operator>(const T &lhs, const T &rhs) noexcept
        {
            return rhs < lhs;
        }

        friend bool operator<=(const T &lhs, const T &rhs) noexcept
        {
            return !(rhs < lhs);
        }

        friend bool operator>=(const T &lhs, const T &rhs) noexcept
        {
            return !(lhs < rhs);
        }

        friend bool operator!=(const T &lhs, const T &rhs) noexcept
        {
            return !(lhs == rhs);
        }
    };
}

#endif //CORE_UTILS_RELATIONAL_HPP
