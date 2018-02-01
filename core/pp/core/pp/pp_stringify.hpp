//
// Created by doom on 13/10/17.
//

#ifndef CORE_PP_STRINGIFY_HPP
#define CORE_PP_STRINGIFY_HPP

#include <string_view>

/** Convert a token to a string litteral */
#define pp_stringify(s)         #s

/** Get the length of a string litteral */
#define pp_strlen(s)            (sizeof(s"") - 1)

/** Convert a token to a string_view */
#define pp_stringviewify(s)     std::string_view(pp_stringify(s), pp_strlen(pp_stringify(s)))

#endif //CORE_PP_STRINGIFY_HPP
