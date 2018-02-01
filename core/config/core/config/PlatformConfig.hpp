//
// Created by szterg_r on 22/08/2017.
//

#ifndef CORE_CONFIG_PLATFORMCONFIG_HPP
#define CORE_CONFIG_PLATFORMCONFIG_HPP

#ifdef _WIN32
# include <core/config/details/WindowsConfig.hpp>
#endif

#ifdef __linux__
# include <core/config/details/LinuxConfig.hpp>
#endif

#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
# include <core/config/details/UnixConfig.hpp>
#endif

#ifdef __APPLE__
# include <core/config/details/OSXConfig.hpp>
#endif

#endif //CORE_CONFIG_PLATFORMCONFIG_HPP
