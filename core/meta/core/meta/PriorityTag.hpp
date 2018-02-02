//
// Created by doom on 18/11/17.
//

#ifndef CORE_META_PRIORITYTAG_HPP
#define CORE_META_PRIORITYTAG_HPP

namespace meta
{
    /**
     * Priority tag class, to control overloading fallbacks.
     */
    template <unsigned int Level>
    struct PriorityTag : public PriorityTag<Level - 1>
    {
    };

    template <>
    struct PriorityTag<0>
    {
    };
}

#endif //CORE_META_PRIORITYTAG_HPP
