//
// Created by doom on 11/10/17.
//

#ifndef CORE_LIB_GETSYMBOL_HPP
#define CORE_LIB_GETSYMBOL_HPP

#include <memory>
#include <core/lib/SharedLibrary.hpp>

namespace lib
{
    template <typename T>
    using Symbol = std::shared_ptr<T>;

    template <typename T>
    Symbol<T> getSymbol(const fs::path &libPath, const std::string &symbolName, LoadingMode mode = LoadingMode::Default)
    {
        auto p = std::make_shared<SharedLibrary>(libPath, mode);

        if (!p->isLoaded()) {
            throw LibraryNotLoaded();
        }
        return Symbol<T>(p, std::addressof(p->get<T>(symbolName)));
    }
}

#endif //CORE_LIB_GETSYMBOL_HPP
