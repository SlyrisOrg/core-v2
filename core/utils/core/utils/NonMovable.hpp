//
// Created by milerius on 23/08/17.
//

#ifndef CORE_UTILS_NONMOVABLE_HPP
#define CORE_UTILS_NONMOVABLE_HPP

namespace utils
{
    /**
     * @class NonMovable
     * @brief Allow a child of this class to be non-movable
     */
    class NonMovable
    {
    protected:
        NonMovable() = default;

        virtual ~NonMovable() noexcept = default;

        NonMovable(NonMovable &&) = delete;

        NonMovable &operator=(NonMovable &&) = delete;
    };
};

#endif //CORE_UTILS_NONMOVABLE_HPP
