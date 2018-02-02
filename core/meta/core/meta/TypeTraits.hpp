//
// Created by doom on 01/02/18.
//

#ifndef CORE_META_TYPETRAITS_HPP
#define CORE_META_TYPETRAITS_HPP

#include <type_traits>

namespace meta
{
    template <template <typename...> typename MetaFunction, typename, typename ...Params>
    struct is_detected : std::false_type
    {
    };

    template <template <typename...> typename MetaFunction, typename ...Params>
    struct is_detected<MetaFunction, std::void_t<MetaFunction<Params...>>, Params...> : std::true_type
    {
    };

    template <typename T, typename U>
    using comparison_t = decltype(std::declval<T &>() == std::declval<U &>());

    template <typename T, typename U>
    using is_eq_comparable_with = is_detected<comparison_t, void, T, U>;

    template <typename T, typename U>
    static constexpr const bool is_eq_comparable_with_v = is_eq_comparable_with<T, U>::value;
};

#endif //CORE_META_TYPETRAITS_HPP