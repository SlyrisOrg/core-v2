//
// Created by milerius on 23/08/17.
//

#ifndef CORE_UTILS_SINGLETON_HPP
#define CORE_UTILS_SINGLETON_HPP

#include <core/utils/NonCopyable.hpp>
#include <core/utils/NonMovable.hpp>

namespace utils
{
    template <typename Base>
    class Singleton : private NonCopyable, private NonMovable
    {
    public:
        static Base &get()
        {
            static Base instance;
            return instance;
        }
    };
}

#endif //CORE_UTILS_SINGLETON_HPP
