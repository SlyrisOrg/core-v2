//
// Created by milerius on 14/02/18.
//

#ifndef CORE_ERASE_IF_HPP
#define CORE_ERASE_IF_HPP

#include <iterator>
#include <unordered_map>
#include <unordered_set>
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

    template <typename Container, typename Functor>
    void erase_if_associative(Container &&container, Functor &&func) noexcept
    {
        for (auto it = std::begin(container); it != std::end(container);) {
            if (func(it->second)) {
                it = container.erase(it);
            } else {
                ++it;
            }
        }
    };

    template<typename Container, typename Functor>
    void erase_if(Container&& container, Functor&& func) noexcept
    {
        container.erase(std::remove_if(begin(container), end(container), func));
    };
}

namespace ctr::range
{
    template<typename T>
    static constexpr bool is_associative_container_v = details::is_associative_container<T>::value;

    template <typename Container, typename Functor>
    void erase_if(Container &&container, Functor &&func) noexcept
    {
        if constexpr (is_associative_container_v<std::decay_t<Container>>)
            details::erase_if_associative(std::forward<Container>(container), std::forward<Functor>(func));
        else
            details::erase_if(std::forward<Container>(container), std::forward<Functor>(func));
    }
}

#endif //CORE_ERASE_IF_HPP
