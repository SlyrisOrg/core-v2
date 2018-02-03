//
// Created by doom on 13/10/17.
//

#ifndef CORE_LIB_LOADINGMODE_HPP
#define CORE_LIB_LOADINGMODE_HPP

#include <core/config/Config.hpp>

namespace lib
{
    enum LoadingMode
    {
#ifdef USING_WINDOWS
        Default = 0,
        RTLDLazy = 0,
        RTLDNow = 0,
        RTLDGlobal = 0,
        RTLDLocal = 0,
        DontResolveAllRefs = DONT_RESOLVE_DLL_REFERENCES,
        IgnoreCodeAuthzLevel = LOAD_IGNORE_CODE_AUTHZ_LEVEL,
        UseAlteredSearchPath = LOAD_WITH_ALTERED_SEARCH_PATH,
        DontAddPrefix = 0, //Windows DLL's don't use any prefix
#else
        Default = 0,
        RTLDLazy = RTLD_LAZY,
        RTLDNow = RTLD_NOW,
        RTLDGlobal = RTLD_GLOBAL,
        RTLDLocal = RTLD_LOCAL,
        DontResolveAllRefs = 0,
        IgnoreCodeAuthzLevel = 0,
        UseAlteredSearchPath = 0,
        DontAddPrefix = 0x80000000, //Set the first bit so we don't collide with other flags
        //RTLDDeepBind = RTLD_DEEPBIND, only for glibc >= 2.3.4 according to man pages, TODO: detect it
#endif
    };

    static always_inline LoadingMode operator|(LoadingMode a, LoadingMode b)
    {
        return static_cast<LoadingMode>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
    }

    static always_inline LoadingMode operator|=(LoadingMode a, LoadingMode b)
    {
        a = a | b;
        return a;
    }

    static always_inline LoadingMode operator&(LoadingMode a, LoadingMode b)
    {
        return static_cast<LoadingMode>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
    }

    static always_inline LoadingMode operator&=(LoadingMode a, LoadingMode b)
    {
        a = a & b;
        return a;
    }

    static always_inline LoadingMode operator~(LoadingMode a)
    {
        return static_cast<LoadingMode>(~static_cast<unsigned int>(a));
    }

    static always_inline LoadingMode operator^(LoadingMode a, LoadingMode b)
    {
        return static_cast<LoadingMode>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
    }

    static always_inline LoadingMode operator^=(LoadingMode a, LoadingMode b)
    {
        a = a ^ b;
        return a;
    }
}

#endif //CORE_LIB_LOADINGMODE_HPP
