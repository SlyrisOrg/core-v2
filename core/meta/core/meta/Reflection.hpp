//
// Created by doom on 25/11/17.
//

#ifndef CORE_META_REFLECTION_HPP
#define CORE_META_REFLECTION_HPP

#include <type_traits>
#include <pp/pp_stringify.hpp>
#include <meta/Map.hpp>

namespace meta
{
    template <typename T, typename = std::void_t<>>
    struct is_reflectible : public std::false_type
    {
    };

    template <typename T>
    struct is_reflectible<T, std::void_t<decltype(T::memberMap())>> : public std::true_type
    {
    };

    template <typename T>
    inline constexpr bool is_reflectible_v = is_reflectible<T>::value;

    namespace details
    {
        constexpr std::string_view skipNamespaceName(const std::string_view v)
        {
            return (v[0] == ':' && v[1] == ':') ? std::string_view{v.data() + 2, v.length() - 2}
                                                : skipNamespaceName({v.data() + 1, v.length() - 1});
        }
    }
}

#define reflect_member(member)          meta::details::skipNamespaceName(pp_stringviewify(member)), member

#define reflect_function(func)          meta::details::skipNamespaceName(pp_stringviewify(func)), func

#define reflect_class(cls)                                                  \
    static const std::string &className() noexcept                          \
    {                                                                       \
        static const std::string name = pp_stringify(cls);                  \
        return name;                                                        \
    }

#define get_reflected_member(m, mb, f)      meta::find(m, mb, f)
#define get_reflected_function(m, mb, f)    meta::find(m, mb, f)

#endif //CORE_META_REFLECTION_HPP
