//
// Created by doom on 12/10/17.
//

#ifndef CORE_LIB_TEST_ITEST_HPP
#define CORE_LIB_TEST_ITEST_HPP

#include <core/utils/NonCopyable.hpp>

struct ITest : utils::NonCopyable
{
    virtual int add(int a, int b) = 0;

    virtual int getLastResult() const noexcept = 0;
};

#endif //CORE_LIB_TEST_ITEST_HPP
