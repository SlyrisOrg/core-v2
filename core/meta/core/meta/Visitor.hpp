//
// Created by doom on 25/11/17.
//

#ifndef CORE_META_VISITOR_HPP
#define CORE_META_VISITOR_HPP

#include <utility>
#include <core/config/CompilerConfig.hpp>

namespace meta
{
#ifdef USING_MSVC
    template <typename ...Funcs>
    class Visitor : public Funcs...
    {
    public:
        constexpr explicit Visitor(Funcs &&...funcs) noexcept : Funcs{std::forward<Funcs>(funcs)}...
        {
        }
    };
#else
    template <typename ...Funcs>
    class Visitor : private Funcs...
    {
    public:
        constexpr explicit Visitor(Funcs &&...funcs) noexcept : Funcs{std::forward<Funcs>(funcs)}...
        {
        }

        using Funcs::operator()...;
    };
#endif

    template <typename ...Funcs>
    auto makeVisitor(Funcs &&...funcs) noexcept
    {
        Visitor<Funcs...> ret(std::forward<Funcs>(funcs)...);

        return ret;
    }
}

#endif //CORE_META_VISITOR_HPP
