//
// Created by doom on 25/08/17.
//

#ifndef CORE_UTILS_LEXICALCAST_HPP
#define CORE_UTILS_LEXICALCAST_HPP

#include <sstream>

namespace utils
{
    /**
     * Lexical Cast
     *
     * This file defines a lexicalCast function that allows converting an object's value to
     * another type. It attempts to detect the appropriate conversion method according to the
     * types of the given objects.
     */

    class BadLexicalCast : public std::bad_cast
    {
    public:
        const char *what() const noexcept override
        {
            return "Bad lexical cast";
        }
    };

    namespace details
    {
        struct UnknownCase
        {
        };

        struct TrivialCase
        {
        };

        template <typename To, typename From>
        struct ChooseLexicalCast
        {
            using type = std::conditional_t<std::is_convertible_v<To, From>, TrivialCase, UnknownCase>;
        };

        template <typename To, typename From>
        using ChooseLexicalCast_t = typename ChooseLexicalCast<To, From>::type;

        /** Default case: through std::stringstream */
        template <typename To, typename From>
        To lexicalCastAux(const From &from, UnknownCase)
        {
            std::stringstream ss;
            To ret;

            ss << from;
            ss >> ret;
            if (ss.fail() || ss.bad())
                throw BadLexicalCast();
            return ret;
        }

        /** Types are compatible: use implicit cast */
        template <typename To, typename From>
        To lexicalCastAux(const From &from, TrivialCase)
        {
            return from;
        }
    };

    template <typename To, typename From>
    To lexicalCast(const From &from)
    {
        return details::lexicalCastAux<To, From>(from, details::ChooseLexicalCast_t<To, From>{});
    }
};

#endif //CORE_UTILS_LEXICALCAST_HPP
