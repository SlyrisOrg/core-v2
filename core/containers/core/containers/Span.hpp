//
// Created by doom on 15/11/17.
//

#ifndef CORE_CONTAINERS_SPAN_HPP
#define CORE_CONTAINERS_SPAN_HPP

#include <cstddef>
#include <type_traits>
#include <core/config/Config.hpp>
#include <core/utils/Relational.hpp>

namespace ctr
{
    namespace details
    {
        template <typename SpanT, bool Const>
        class SpanIterator : public utils::Relational<SpanIterator<SpanT, Const>>
        {
        public:
            using ContainedT = typename SpanT::ContainedT;
            using Reference = std::conditional_t<Const, const ContainedT &, ContainedT &>;
            using Pointer = std::conditional_t<Const, const ContainedT *, ContainedT *>;
            using DiffType = std::ptrdiff_t;

            //STL iterator fixups
            using iterator_category = std::random_access_iterator_tag;
            using value_type = ContainedT;
            using reference = Reference;
            using pointer = Pointer;
            using difference_type = DiffType;

            SpanIterator() noexcept : _spanPtr(nullptr), _cur(0)
            {
            }

            SpanIterator(const SpanT *sp, Pointer cur) noexcept : _spanPtr(sp), _cur(cur)
            {
            }

            ~SpanIterator() noexcept = default;

            SpanIterator(const SpanIterator &) noexcept = default;
            SpanIterator(SpanIterator &&) noexcept = default;

            SpanIterator &operator=(const SpanIterator &) noexcept = default;
            SpanIterator &operator=(SpanIterator &&) noexcept = default;

            operator SpanIterator<SpanT, true>() const noexcept
            {
                return SpanIterator<SpanT, true>(*this);
            }

            bool operator==(const SpanIterator &other) const noexcept
            {
                return _spanPtr == other._spanPtr && _cur == other._cur;
            }

            bool operator<(const SpanIterator &other) const noexcept
            {
                return _cur < other._cur;
            }

            SpanIterator &operator++() noexcept
            {
                ++_cur;
                return *this;
            }

            SpanIterator operator++(int) noexcept
            {
                auto tmp = *this;

                ++(*this);
                return tmp;
            }

            SpanIterator &operator--() noexcept
            {
                --_cur;
                return *this;
            }

            SpanIterator operator--(int) noexcept
            {
                auto tmp = *this;

                --(*this);
                return tmp;
            }

            SpanIterator operator+(DiffType add) const noexcept
            {
                return SpanIterator(_spanPtr, _cur + add);
            }

            SpanIterator operator-(DiffType add) const noexcept
            {
                return SpanIterator(_spanPtr, _cur - add);
            }

            DiffType operator-(const SpanIterator &other) const noexcept
            {
                return _cur - other._cur;
            }

            Reference operator*() noexcept
            {
                return *_cur;
            }

            Reference operator*() const noexcept
            {
                return *_cur;
            }

            Pointer operator->() noexcept
            {
                return _cur;
            }

            Pointer operator->() const noexcept
            {
                return _cur;
            }

        private:
            const SpanT *_spanPtr;
            Pointer _cur;
        };
    }

    template <typename T>
    class Span : public utils::Relational<Span<T>>
    {
    public:
        using ThisType = Span<T>;
        using ContainedT = T;
        using Value = std::remove_cv_t<ContainedT>;
        using Pointer = std::add_pointer_t<ContainedT>;
        using Iterator = details::SpanIterator<ThisType, false>;
        using ConstIterator = details::SpanIterator<ThisType, true>;
        using ReverseIterator = std::reverse_iterator<Iterator>;
        using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

        constexpr Span() noexcept : _data(nullptr), _size(0)
        {
        }

        constexpr Span(Pointer ptr, std::size_t size) noexcept : _data(ptr), _size(size)
        {
        }

        constexpr Span(Pointer begin, Pointer end) noexcept : _data(begin), _size(end - begin)
        {
        }

        template <std::size_t ArraySize>
        constexpr Span(ContainedT (&array)[ArraySize]) noexcept : _data(&array[0]), _size(ArraySize)
        {
        }

        template <size_t N>
        constexpr Span(const std::array<T, N> &array) noexcept : _data(array.data()), _size(N)
        {
        }

        template <size_t N>
        constexpr Span(std::array<T, N> &array) noexcept : _data(array.data()), _size(N)
        {
        }

        template <typename ContainerT,
            typename = std::enable_if_t<std::is_convertible_v<decltype(std::declval<ContainerT>().data()), Pointer>>>
        constexpr Span(ContainerT &cont) noexcept : _data(cont.data()), _size(cont.size())
        {
        }

        template <typename IteratorT,
            typename = std::enable_if_t<std::is_convertible_v<decltype(*std::declval<IteratorT>()), ContainedT>>>
        constexpr Span(IteratorT beg, IteratorT end) noexcept : _data(&(*beg)), _size(end - beg)
        {
        }

        ~Span() noexcept = default;

        constexpr Span(const Span &) noexcept = default;
        constexpr Span(Span &&) noexcept = default;

        constexpr Span &operator=(const Span &) noexcept = default;

        constexpr Span &operator=(Span &&) noexcept = default;

        constexpr Span subspan(std::size_t from, std::size_t length) const
        {
            if (unlikely(from > size()))
                throw std::out_of_range("subspan index out of range");
            return {_data + from, _data + from + length};
        }

        Iterator begin() noexcept
        {
            return {this, _data};
        }

        ConstIterator begin() const noexcept
        {
            return {this, _data};
        }

        Iterator end() noexcept
        {
            return {this, _data + _size};
        }

        ConstIterator end() const noexcept
        {
            return {this, _data + _size};
        }

        ReverseIterator rbegin() noexcept
        {
            return ReverseIterator(end());
        }

        ConstReverseIterator rbegin() const noexcept
        {
            return ConstReverseIterator(end());
        }

        ReverseIterator rend() noexcept
        {
            return ReverseIterator(begin());
        }

        ConstReverseIterator rend() const noexcept
        {
            return ConstReverseIterator(begin());
        }

        constexpr Value operator[](std::size_t idx) const noexcept
        {
            return _data[idx];
        }

        Value at(std::size_t idx) const noexcept
        {
            if (unlikely(idx >= _size)) {
                throw std::out_of_range("Span::at(): index out of range");
            }
            return operator[](idx);
        }

        Pointer data() noexcept
        {
            return _data;
        }

        const Pointer data() const noexcept
        {
            return _data;
        }

        constexpr std::size_t size() const noexcept
        {
            return _size;
        }

        constexpr bool empty() const noexcept
        {
            return _size == 0;
        }

        constexpr bool operator==(const Span &other) const noexcept
        {
            return std::equal(begin(), end(), other.begin(), other.end());
        }

        constexpr bool operator<(const Span &other) const noexcept
        {
            return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
        }

    private:
        Pointer _data;
        std::size_t _size;
    };
}

#endif //CORE_CONTAINERS_SPAN_HPP
