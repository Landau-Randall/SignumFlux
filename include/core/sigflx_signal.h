#pragma once
#include <type_traits>
#include <cstddef>
#include <iterator>
#include "sigflx_lib/sigflx_allocators_aligned.h"

namespace SignumFlux
{
template<typename T,typename Allocator = Allocators::AlignedAllocator<T>>
class Signal
{
public:
    using ValueType = T;
    using SizeType = std::size_t;
    using Pointer = T *;
    using ConstPointer = const T *;
    using Reference = T &;
    using ConstReference = const T &;
    using AllocatorType = Allocator;
    using SignalIterator = T *;
    using ConstSignalIterator = const T *;
private:
    Pointer data_ = nullptr;
    SizeType frames_ = 0;
    double sampleRate_ = 1.0;
    double duration_ = 0.0;
    AllocatorType allocator_;
public:
    Signal();
    Signal(const Signal & object);
    Signal(const Signal & object,const AllocatorType & allocator);
    Signal(Signal && object) noexcept;

    Signal(SizeType frames,double sampleRate);
    Signal(SizeType frames,double sampleRate,const AllocatorType & allocator);
    Signal(T * data,SizeType frames,double sampleRate);
    Signal(T * data,SizeType frames,double sampleRate,const AllocatorType & allocator);

    ~Signal();

    Signal & operator=(const Signal & object);
    Signal & operator=(Signal && object) noexcept;

    Reference operator()(SizeType frame);
    ConstReference operator()(SizeType frame) const;
    Reference at(SizeType frame);
    ConstReference at(SizeType frame) const;

    Pointer data() noexcept { return data_; };
    ConstPointer data() const noexcept { return data_; };
    SizeType frames() const noexcept { return frames_; };
    double sampleRate() const noexcept { return sampleRate_; };
    double duration() const noexcept { return duration_; };
    bool empty() const noexcept { return frames_ == 0; };

    void resize(SizeType newFrames);
    void clear();
    void release();
    void swap(Signal & object);

    void fill(const T & value);

    SignalIterator begin() noexcept;
    SignalIterator end() noexcept;
    ConstSignalIterator cbegin() const noexcept;
    ConstSignalIterator cend() const noexcept;
};

template<typename T,typename Allocator>
void swap(Signal<T,Allocator> & first,Signal<T,Allocator> & second) noexcept;
}

#include "../../src/core/sigflx_signal.tpp"