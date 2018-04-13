//
// Created by doom on 03/11/17.
//

#ifndef CORE_LIB_ALIAS_HPP
#define CORE_LIB_ALIAS_HPP

#include <core/config/CompilerHints.hpp>

#if defined(USING_WINDOWS)
#define __alias_section__           __pragma(section("__lib", read)) __declspec(allocate("__lib"))
#elif defined(USING_LINUX)
#define __alias_section__           __attribute__ ((section ("__lib")))
#else
#define __alias_section__           __attribute__ ((section ("__DATA__lib")))
#endif

#define lib_alias_function(name, alias_name)                                \
    extern "C" exported_symbol const void *alias_name;                        \
    const void *alias_name = reinterpret_cast<const void *>(name);

#endif //CORE_LIB_ALIAS_HPP
