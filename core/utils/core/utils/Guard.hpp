//
// Created by doom on 21/09/17.
//

#ifndef CORE_UTILS_GUARD_HPP
#define CORE_UTILS_GUARD_HPP

#include <functional>
#include <core/utils/NonCopyable.hpp>

namespace utils
{
    template <typename T>
    class Guard : private utils::NonCopyable
    {
    public:
        using CleanupFuncT = std::function<void(T &)>;

        Guard(T &&value, const CleanupFuncT &cleanup) : _value(std::forward<T>(value)), _cleanup(cleanup)
        {
        }

        template <typename ...Args>
        Guard(Args &&...args, const CleanupFuncT &cleanup) : _value(std::forward<Args>(args)...), _cleanup(cleanup)
        {
        }

        ~Guard()
        {
            if (_needsCleanup) {
                _cleanup(_value);
            }
        }

        Guard(Guard<T> &&other) : _value(std::move(other._value)), _cleanup(std::move(other._cleanup))
        {
            other._needsCleanup = false;
        }

        Guard &operator=(Guard<T> &&other) noexcept
        {
            _value = std::move(other._value);
            _cleanup = std::move(other._cleanup);
            other._needsCleanup = false;
            return *this;
        }

        T *operator->() noexcept
        {
            return &_value;
        }

        const T *operator->() const noexcept
        {
            return &_value;
        }

        const T &get() const noexcept
        {
            return _value;
        }

        T &get() noexcept
        {
            return _value;
        }

    private:
        T _value;
        CleanupFuncT _cleanup;
        bool _needsCleanup{true};
    };
}

#endif //CORE_GUARD_HPP
