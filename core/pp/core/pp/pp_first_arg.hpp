//
// Created by doom on 03/10/17.
//

#ifndef CORE_PP_FIRST_ARG_HPP
#define CORE_PP_FIRST_ARG_HPP

#ifdef _MSC_VER
#define __FIRST_ARG_(f, ...)    f
#define __FIRST_ARG(args)       __FIRST_ARG_ args
#define pp_first_arg(...)       __FIRST_ARG((__VA_ARGS__))
#else
#define pp_first_arg(f, ...)    f
#endif

#endif //CORE_PP_FIRST_ARG_HPP
