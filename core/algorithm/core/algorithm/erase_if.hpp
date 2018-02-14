//
// Created by milerius on 14/02/18.
//

#ifndef CORE_ALGORITHM_ERASE_IF_HPP
#define CORE_ALGORITHM_ERASE_IF_HPP

#include <iterator>
#include <algorithm>
#include <core/meta/TypeTraits.hpp>

namespace algo::details
{
    template<typename T>
    using associative_compare_t = decltype(std::declval<T &>()[std::declval<const typename T::key_type &>()]);

    template<typename T>
    using is_associative_container = meta::is_detected<associative_compare_t, T>;

#define noexcept_if(x)  noexcept(noexcept(x))

    template <typename Container, typename Functor,
        typename ValueType = typename std::decay_t<Container>::value_type>
    static inline void erase_if_associative(Container &&container,
                                            Functor &&func) noexcept_if(func(std::declval<ValueType>()))
    {
        for (auto it = std::begin(container); it != std::end(container);) {
            if (func(*it)) {
                it = container.erase(it);
            } else {
                ++it;
            }
        }
    }

    template <typename Container, typename Functor, typename ValueType = typename std::decay_t<Container>::value_type>
    static inline void erase_if(Container &&container, Functor &&func) noexcept_if(func(std::declval<ValueType>()))
    {
        container.erase(std::remove_if(std::begin(container), std::end(container), func));
    }
}

namespace algo
{
    template <typename T>
    static constexpr bool is_associative_container_v = details::is_associative_container<T>::value;

    template <typename Container, typename Functor,
        std::enable_if_t<is_associative_container_v<std::decay_t<Container>>, bool> = true>
    static inline void erase_if(Container &&container,
                                Functor &&func) noexcept_if(details::erase_if_associative(std::declval<Container>(),
                                                                                          std::declval<Functor>()))
    {
        details::erase_if_associative(std::forward<Container>(container), std::forward<Functor>(func));
    }

    template <typename Container, typename Functor,
        std::enable_if_t<!is_associative_container_v<std::decay_t<Container>>, bool> = true>
    static inline void erase_if(Container &&container,
                                Functor &&func) noexcept_if(details::erase_if(std::declval<Container>(),
                                                                              std::declval<Functor>()))
    {
        details::erase_if(std::forward<Container>(container), std::forward<Functor>(func));
    }

#undef noexcept_if
}

#endif //CORE_ALGORITHM_ERASE_IF_HPP
