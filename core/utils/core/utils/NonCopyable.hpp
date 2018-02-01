//
// Created by milerius on 23/08/17.
//

#ifndef CORE_UTILS_NONCOPYABLE_HPP
#define CORE_UTILS_NONCOPYABLE_HPP

namespace utils
{
    class NonCopyable
    {
    protected:
        NonCopyable() noexcept = default;

        ~NonCopyable() noexcept = default;

        /**
         * @brief Prevent the copy construction of a NonCopyable object.
         */
        NonCopyable(NonCopyable const &other) = delete;

        /**
         * @brief Prevent the copy assignement of a NonCopyable object.
         */
        NonCopyable &operator=(NonCopyable const &other) = delete;
    };
}

#endif //CORE_UTILS_NONCOPYABLE_HPP
