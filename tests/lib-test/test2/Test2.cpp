//
// Created by doom on 12/10/17.
//

#include <core/lib/Alias.hpp>
#include "Test2.hpp"

int Test2Struct::add(int a, int b)
{
    _result = a + b;
    return _result;
}

int Test2Struct::getLastResult() const noexcept
{
    return _result;
}

Test2Struct *Test2Struct::create() noexcept
{
    return new Test2Struct();
}

std::shared_ptr<Test2Struct> Test2Struct::createSharedPtr() noexcept
{
    return std::make_shared<Test2Struct>();
}

lib_alias_function(Test2Struct::create, create);
lib_alias_function(Test2Struct::createSharedPtr, createSharedPtr);
