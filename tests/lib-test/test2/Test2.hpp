//
// Created by doom on 12/10/17.
//

#ifndef CORE_LIB_TEST_TEST2_HPP
#define CORE_LIB_TEST_TEST2_HPP

#include <memory>
#include "ITest2.hpp"

class Test2Struct : public ITest2
{
public:
    int add(int a, int b) override;

    int getLastResult() const noexcept override;

    static Test2Struct *create() noexcept;
    static std::shared_ptr<Test2Struct> createSharedPtr() noexcept;

private:
    int _result;
};

#endif //CORE_LIB_TEST_TEST2_HPP
