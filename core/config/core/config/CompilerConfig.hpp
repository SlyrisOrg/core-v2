//
// Created by szterg_r on 22/08/2017.
//

#ifndef CORE_UTILS_COMPILERCONFIG_HPP
#define CORE_UTILS_COMPILERCONFIG_HPP

#if (defined(__GNUC__) && !defined(__clang__))
# include <core/config/details/Gcc.hpp>
#elif defined _MSC_VER
# include <core/config/details/Msvc.hpp>
#elif defined __clang__
# include <core/config/details/Clang.hpp>
#endif

#endif //CORE_UTILS_COMPILERCONFIG_HPP
