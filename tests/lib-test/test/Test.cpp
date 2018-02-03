//
// Created by doom on 12/10/17.
//

#include <core/config/Config.hpp>
#include "Test.hpp"

int TestStruct::add(int a, int b)
{
    _result = a + b;
    return _result;
}

int TestStruct::getLastResult() const noexcept
{
    return _result;
}

extern "C" EXPORT_SYMBOL TestStruct testInstance;

TestStruct testInstance;
