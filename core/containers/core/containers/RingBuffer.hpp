//
// Created by doom on 25/08/17.
//

#ifndef CORE_CONTAINERS_RINGBUFFER_HPP
#define CORE_CONTAINERS_RINGBUFFER_HPP

#include <cstddef>
#include <utility>
#include <memory>
#include <type_traits>

namespace ctr
{
    namespace details
    {
        template <typename RingBuffT, typename ContainedT>
        class RingBufferIterator : public std::iterator<std::input_iterator_tag, ContainedT>
        {
        private:
            const RingBuffT *_buffPtr;
            ContainedT *_cur;

        public:
            RingBufferIterator(const RingBuffT *buffPtr, ContainedT *cur = nullptr) noexcept :
                _buffPtr(buffPtr), _cur(cur)
            {
            }

            RingBufferIterator() noexcept : _buffPtr(nullptr), _cur(nullptr)
            {
            }

            RingBufferIterator(const RingBufferIterator &) noexcept = default;
            RingBufferIterator(RingBufferIterator &&) noexcept = default;

            ~RingBufferIterator() noexcept = default;

            RingBufferIterator &operator++() noexcept
            {
                // assert(_cur != nullptr);
                _buffPtr->__incPtr(_cur);
                if (_cur == _buffPtr->_curEnd) {
                    _cur = nullptr;
                }
                return *this;
            }

            RingBufferIterator operator++(int) noexcept
            {
                auto tmp = *this;

                ++(*this);
                return tmp;
            }

            RingBufferIterator &operator--() noexcept
            {
                // assert(_cur != _buffPtr->begin());
                if (_cur == nullptr)
                    _cur = _buffPtr->_curEnd;
                _buffPtr->__decPtr(_cur);
                return *this;
            }

            RingBufferIterator operator--(int) noexcept
            {
                auto tmp = *this;

                --(*this);
                return tmp;
            }

            bool operator==(const RingBufferIterator &other) const noexcept
            {
                /**
                 * We compare _buffPtr because in the case of a move/swap, an iterator
                 * from the source should not be considered equal to an iterator of the
                 * target of the move/swap operation.
                 */
                return _buffPtr == other._buffPtr && _cur == other._cur;
            }

            bool operator!=(const RingBufferIterator &other) const noexcept
            {
                return !(*this == other);
            }

            ContainedT &operator*() noexcept
            {
                return *_cur;
            }

            const ContainedT &operator*() const noexcept
            {
                return *_cur;
            }
        };
    }

    template <typename T, bool Overwrite = false>
    class RingBuffer
    {
    private:
        using ThisT = RingBuffer<T, Overwrite>;
        using ContainedT = T;

        friend details::RingBufferIterator<ThisT, ContainedT>;

        T *_buff;
        T *_buffEnd;
        T *_curStart;
        T *_curEnd;
        size_t _capacity;
        size_t _size;

        // These are templates only because we need two versions of each function depending on the constness
        template <typename Ptr>
        void __incPtr(Ptr &toInc) const noexcept
        {
            if (++toInc == _buffEnd) {
                toInc = _buff;
            }
        }

        template <typename Ptr>
        void __decPtr(Ptr &toDec) const noexcept
        {
            if (toDec == _buff) {
                toDec = _buffEnd;
            }
            --toDec;
        }

        void __incStart() noexcept
        {
            __incPtr(_curStart);
        }

        void __incEnd() noexcept
        {
            __incPtr(_curEnd);
        }

        T *__offset(T *ptr, ptrdiff_t offset) const noexcept
        {
            if (ptr + offset >= _buffEnd) {
                //better than returning _buff + (ptr + offset - _buffEnd)
                offset -= _capacity;
            }
            return ptr + offset;
        }

    public:
        explicit RingBuffer(size_t cap = 5) : _buff(new T[cap]), _buffEnd(_buff + cap),
                                              _curStart(_buff), _curEnd(_buff), _capacity(cap), _size(0)
        {
        }

        virtual ~RingBuffer() noexcept
        {
            delete[] _buff;
        }

        RingBuffer(const RingBuffer &other) : _buff(new T[other._capacity]),
                                              _buffEnd(_buff + other._capacity),
                                              _curStart(_buff), _capacity(other._capacity),
                                              _size(other._size)
        {
            _curEnd = std::uninitialized_copy(other.begin(), other.end(), _buff);
        }

        RingBuffer(RingBuffer &&other) noexcept : _buff(nullptr), _buffEnd(nullptr), _curStart(nullptr),
                                                  _curEnd(nullptr), _capacity(0), _size(0)
        {
            std::swap(_buff, other._buff);
            std::swap(_buffEnd, other._buffEnd);
            std::swap(_curStart, other._curStart);
            std::swap(_curEnd, other._curEnd);
            std::swap(_capacity, other._capacity);
            std::swap(_size, other._size);
        }

        RingBuffer &operator=(const RingBuffer &other)
        {
            if (this != &other) {
                delete[] _buff;
                _buff = new T[other._capacity];
                _buffEnd = _buff + other._capacity;
                _curStart = _buff;
                _capacity = other._capacity;
                _size = other._size;
                _curEnd = std::uninitialized_copy(other.begin(), other.end(), _buff);
            }
            return *this;
        }

        RingBuffer &operator=(RingBuffer &&other) noexcept
        {
            if (this != &other) {
                std::swap(_buff, other._buff);
                std::swap(_buffEnd, other._buffEnd);
                std::swap(_curStart, other._curStart);
                std::swap(_curEnd, other._curEnd);
                std::swap(_capacity, other._capacity);
                std::swap(_size, other._size);
            }
            return *this;
        }

        size_t size() const noexcept
        {
            return _size;
        }

        bool empty() const noexcept
        {
            return size() == 0;
        }

        size_t avail() const noexcept
        {
            return _capacity - size();
        }

        bool full() const noexcept
        {
            return avail() == 0;
        }

        template <bool ov = Overwrite>
        typename std::enable_if_t<ov, bool> push(T &&t) noexcept
        {
            bool willOv = full();

            *_curEnd = std::forward<T>(t);
            __incEnd();
            if (willOv)
                __incStart();
            else
                _size += 1;
            return true;
        }

        template <bool ov = Overwrite>
        typename std::enable_if_t<!ov, bool> push(T &&t) noexcept
        {
            if (full())
                return false;
            *_curEnd = std::forward<T>(t);
            __incEnd();
            _size += 1;
            return true;
        }

        bool push(const T &t) noexcept
        {
            T cpy(t);

            return push(std::move(cpy));
        }

        void pop() noexcept
        {
            _size -= 1;
            __incStart();
        }

        using Iterator = details::RingBufferIterator<ThisT, ContainedT>;

        Iterator begin() noexcept
        {
            return Iterator(this, empty() ? nullptr : _curStart);
        }

        Iterator begin() const noexcept
        {
            return Iterator(this, empty() ? nullptr : _curStart);
        }

        Iterator end() noexcept
        {
            /** The end() iterator contains a nullptr */
            return Iterator(this);
        }

        Iterator end() const noexcept
        {
            /** The end() iterator contains a nullptr */
            return Iterator(this);
        }

        T &front() noexcept
        {
            // assert(!empty());
            return *_curStart;
        }

        const T &front() const noexcept
        {
            // assert(!empty());
            return _curStart;
        }

        const T &operator[](size_t idx) const noexcept
        {
            // assert(idx < size());
            return *__offset(_curStart, idx);
        }

        T &operator[](size_t idx) noexcept
        {
            // assert(idx < size());
            return *__offset(_curStart, idx);
        }
    };
}

#endif //CORE_CONTAINERS_RINGBUFFER_HPP
