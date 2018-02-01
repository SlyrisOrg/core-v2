//
// Created by doom on 29/09/17.
//

#ifndef CORE_CONFIG_ENDIAN_HPP
#define CORE_CONFIG_ENDIAN_HPP

#include <cstdint>

namespace config
{
    constexpr bool hasLittleEndian() noexcept
    {
        constexpr uint32_t num = 0xAABBCCDD;
        constexpr uint8_t firstByte = (const uint8_t &)(num);
        return firstByte == 0xDD;
    }

    constexpr bool hasBigEndian() noexcept
    {
        constexpr uint32_t num = 0xAABBCCDD;
        constexpr uint8_t firstByte = (const uint8_t &)(num);
        return firstByte == 0xAA;
    }
}

#endif //CORE_CONFIG_ENDIAN_HPP
