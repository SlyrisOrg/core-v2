//
// Created by doom on 18/09/17.
//

#ifndef CORE_UTILS_ENUMS_HPP
#define CORE_UTILS_ENUMS_HPP

#include <string_view>
#include <string>
#include <array>
#include <core/pp/PP.hpp>

#define __SIZEOF_TAB(tab)       (sizeof(tab) / sizeof((tab)[0]))

#define __DO_CASE_STR(value)                                                \
    case value:                                                             \
        return #value;                                                      \

#define __STRINGIFY_ELEM(v)       pp_stringviewify(v),

# define __ENUM_MAKE(name, decl_kw, super_expr, ...)                        \
    class name                                                              \
    {                                                                       \
    public:                                                                 \
        decl_kw enum_##name super_expr                                      \
        {                                                                   \
            __VA_ARGS__                                                     \
        };                                                                  \
                                                                            \
        using EnumType = enum_##name;                                       \
                                                                            \
        constexpr name() noexcept : _value(pp_first_arg(__VA_ARGS__))       \
        {                                                                   \
        }                                                                   \
                                                                            \
        constexpr name(EnumType value) noexcept : _value(value)             \
        {                                                                   \
        }                                                                   \
                                                                            \
        name &operator=(EnumType value) noexcept                            \
        {                                                                   \
            _value = value;                                                 \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        static constexpr const std::array<name,                             \
                            pp_count_args(__VA_ARGS__)> values() noexcept   \
        {                                                                   \
            return {{__VA_ARGS__}};                                         \
        }                                                                   \
                                                                            \
        static constexpr size_t size() noexcept                             \
        {                                                                   \
            return pp_count_args(__VA_ARGS__);                              \
        }                                                                   \
                                                                            \
        class InvalidConversion : public std::exception                     \
        {                                                                   \
        public:                                                             \
            const char *what() const noexcept override                      \
            {                                                               \
                return "Unable to convert this string to an enum value";    \
            }                                                               \
        };                                                                  \
                                                                            \
    private:                                                                \
        enum_##name _stringToValue(const std::string_view v)                \
        {                                                                   \
            static constexpr const std::string_view strTab[] = {            \
                pp_for_each(__STRINGIFY_ELEM, __VA_ARGS__)                  \
            };                                                              \
            static constexpr const auto vals = values();                    \
                                                                            \
            for (size_t i = 0; i < __SIZEOF_TAB(strTab); ++i) {             \
                if (strTab[i] == v) {                                       \
                    return vals[i];                                         \
                }                                                           \
            }                                                               \
            throw InvalidConversion();                                      \
        }                                                                   \
                                                                            \
    public:                                                                 \
        name(const std::string_view v) : _value(_stringToValue(v))          \
        {                                                                   \
        }                                                                   \
                                                                            \
        name &operator=(const std::string_view v)                           \
        {                                                                   \
            _value = _stringToValue(v);                                     \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        operator EnumType() const noexcept                                  \
        {                                                                   \
            return _value;                                                  \
        }                                                                   \
                                                                            \
        std::string toString() const noexcept                               \
        {                                                                   \
            switch (_value) {                                               \
                pp_for_each(__DO_CASE_STR, __VA_ARGS__)                     \
                default:                                                    \
                    return "";                                              \
            }                                                               \
        }                                                                   \
                                                                            \
        static std::string toString(name v)                                 \
        {                                                                   \
            return v.toString();                                            \
        }                                                                   \
                                                                            \
    private:                                                                \
        EnumType _value;                                                    \
    };

#define ENUM(name, ...) __ENUM_MAKE(name, enum, , __VA_ARGS__)

#endif //CORE_UTILS_ENUMS_HPP
