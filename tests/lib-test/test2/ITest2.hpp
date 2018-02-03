//
// Created by doom on 12/10/17.
//

#ifndef CORE_LIB_TEST_ITEST2_HPP
#define CORE_LIB_TEST_ITEST2_HPP

#include <core/utils/NonCopyable.hpp>

struct ITest2 : utils::NonCopyable
{
    virtual int add(int a, int b) = 0;
    virtual int getLastResult() const noexcept = 0;
    virtual ~ITest2() noexcept = default;
};

#endif //CORE_LIB_TEST_ITEST_HPP
