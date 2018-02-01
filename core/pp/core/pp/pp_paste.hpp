//
// Created by doom on 03/10/17.
//

#ifndef CORE_PP_PASTE_HPP
#define CORE_PP_PASTE_HPP

#define __PP_PASTE_HELPER(a, b)     a##b
#define pp_paste(a, b)              __PP_PASTE_HELPER(a, b)

#endif //CORE_PP_PASTE_HPP
