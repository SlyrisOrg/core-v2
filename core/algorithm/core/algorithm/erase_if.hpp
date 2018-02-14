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
    template <typename T>
    using has_key_type_t = decltype(std::declval<typename T::key_type>());

    template <typename T>
    using has_value_type_t = decltype(std::declval<typename T::value_type>());

    template <typename T>
    using is_associative_container = std::conjunction<meta::is_detected<has_key_type_t, T>, meta::is_detected<has_value_type_t, T>>;

    template <typename T>
    static inline constexpr bool is_associative_container_v = is_associative_container<T>::value;

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
        container.erase(std::remove_if(std::begin(container), std::end(container), func), std::end(container));
    }
}

namespace algo
{
    template <typename Container, typename Functor,
        std::enable_if_t<details::is_associative_container_v<std::decay_t<Container>>, bool> = true>
    static inline void erase_if(Container &&container,
                                Functor &&func) noexcept_if(details::erase_if_associative(std::declval<Container>(),
                                                                                          std::declval<Functor>()))
    {
        details::erase_if_associative(std::forward<Container>(container), std::forward<Functor>(func));
    }

    template <typename Container, typename Functor,
        std::enable_if_t<!details::is_associative_container_v<std::decay_t<Container>>, bool> = true>
    static inline void erase_if(Container &&container,
                                Functor &&func) noexcept_if(details::erase_if(std::declval<Container>(),
                                                                              std::declval<Functor>()))
    {
        details::erase_if(std::forward<Container>(container), std::forward<Functor>(func));
    }

#undef noexcept_if
}

#endif //CORE_ALGORITHM_ERASE_IF_HPP
