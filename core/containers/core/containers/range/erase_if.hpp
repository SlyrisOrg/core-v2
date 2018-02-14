//
// Created by milerius on 14/02/18.
//

#ifndef CORE_ERASE_IF_HPP
#define CORE_ERASE_IF_HPP

#include <iterator>
#include <algorithm>

namespace ctr::range::details
{
    template <typename T, typename U = void>
    struct is_associative_container : std::false_type
    {
    };

    template <typename T>
    struct is_associative_container<T, std::void_t<typename T::key_type, typename T::mapped_type,
        decltype(std::declval<T &>()[std::declval<const typename T::key_type &>()])>>
        : std::true_type
    {
    };

#define noexcept_if(x)  noexcept(noexcept(x))

    template <typename Container, typename Functor, typename ValueType = typename std::decay_t<Container>::value_type::second_type>
    void erase_if_associative(Container &&container, Functor &&func) noexcept_if(func(std::declval<ValueType>()))
    {
        for (auto it = std::begin(container); it != std::end(container);) {
            if (func(it->second)) {
                it = container.erase(it);
            } else {
                ++it;
            }
        }
    }

    template <typename Container, typename Functor, typename ValueType = typename std::decay_t<Container>::value_type>
    void erase_if(Container &&container, Functor &&func) noexcept_if(func(std::declval<ValueType>()))
    {
        container.erase(std::remove_if(std::begin(container), std::end(container), func));
    }
}

namespace ctr::range
{
    template <typename T>
    static constexpr bool is_associative_container_v = details::is_associative_container<T>::value;

    template <typename Container, typename Functor, std::enable_if_t<is_associative_container_v<std::decay_t<Container>>, bool> = true>
    void erase_if(Container &&container,
                  Functor &&func) noexcept_if(details::erase_if_associative(std::declval<Container>(),
                                                                            std::declval<Functor>()))
    {
        details::erase_if_associative(std::forward<Container>(container), std::forward<Functor>(func));
    }

    template <typename Container, typename Functor, std::enable_if_t<!is_associative_container_v<std::decay_t<Container>>, bool> = true>
    void erase_if(Container &&container,
                  Functor &&func) noexcept_if(details::erase_if(std::declval<Container>(),
                                                                std::declval<Functor>()))
    {
        details::erase_if(std::forward<Container>(container), std::forward<Functor>(func));
    }

#undef noexcept_if
}

#endif //CORE_ERASE_IF_HPP
