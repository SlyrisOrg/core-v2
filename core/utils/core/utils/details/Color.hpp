//
// Created by roman sztergbaum on 10/09/2017.
//

#ifndef CORE_UTILS_DETAILS_COLOR_HPP
#define CORE_UTILS_DETAILS_COLOR_HPP

#include <core/config/Environment.hpp>

#if defined(USING_UNIX)
#include <core/utils/details/UnixColor.hpp>
#elif defined(USING_WINDOWS)
#include <core/utils/details/WindowsColor.hpp>
#endif

#endif //CORE_UTILS_DETAILS_COLOR_HPP
