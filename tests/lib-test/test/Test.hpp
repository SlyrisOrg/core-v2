//
// Created by doom on 12/10/17.
//

#ifndef CORE_LIB_TEST_TEST_HPP
#define CORE_LIB_TEST_TEST_HPP

#include "ITest.hpp"

class TestStruct : public ITest
{
public:
    int add(int a, int b) override;

    int getLastResult() const noexcept override;

private:
    int _result;
};

#endif //CORE_LIB_TEST_TEST_HPP
