#include "core/sigflx_signal.h"
#include <algorithm>
#include <stdexcept>

namespace SignumFlux
{
template<typename T,typename Allocator>
Signal<T,Allocator>::Signal()
{

}

template <typename T, typename Allocator>
Signal<T, Allocator>::Signal(const Signal &object): 
frames_(object.frames_),
sampleRate_(object.sampleRate_),
duration_(object.duration_),
allocator_(object.allocator_)
{
    if (object.data_ != nullptr)
    {
        data_ = allocator_.allocate(frames_);
        std::copy(object.data_,object.data_ + object.frames_,data_);
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(const Signal & object,const AllocatorType & allocator):
frames_(object.frames_),
sampleRate_(object.sampleRate_),
duration_(object.duration_),
allocator_(allocator)
{
    if (object.data_ != nullptr)
    {
        data_ = allocator_.allocate(frames_);
        std::copy(object.data_,object.data_ + object.frames_,data_);
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(Signal && object) noexcept:
data_(object.data_),
frames_(object.frames_),
sampleRate_(object.sampleRate_),
duration_(object.duration_),
allocator_(std::move(object.allocator_))
{
    object.data_ = nullptr;
    object.frames_ = 0;
    object.sampleRate_ = 1.0;
    object.duration_ = 0.0;
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(SizeType frames,double sampleRate):
frames_(frames),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_()
{
    data_ = allocator_.allocate(frames_);
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(SizeType frames,double sampleRate,const AllocatorType & allocator):
frames_(frames),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_(allocator)
{
    data_ = allocator_.allocate(frames_);
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(T * data,SizeType frames,double sampleRate):
frames_(frames),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_()
{
    if (data != nullptr)
    {
        data_ = allocator_.allocate(frames_);
        std::copy(data,data + frames_,data_);
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::Signal(T * data,SizeType frames,double sampleRate,const AllocatorType & allocator):
frames_(frames),
sampleRate_(sampleRate),
duration_(static_cast<double>(frames) / sampleRate),
allocator_(allocator)
{
    if (data != nullptr)
    {
        data_ = allocator_.allocate(frames_);
        std::copy(data,data + frames_,data_);
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator>::~Signal()
{
    if (data_ != nullptr)
    {
        allocator_.deallocate(data_,frames_);
        data_ = nullptr;
    }
}

template<typename T,typename Allocator>
Signal<T,Allocator> & Signal<T,Allocator>::operator=(const Signal & object)
{
    Signal temp(object);
    swap(temp);
    return *this;
}

template<typename T,typename Allocator>
Signal<T,Allocator> & Signal<T,Allocator>::operator=(Signal && object) noexcept
{
    if (this != &object)
    {
        Signal temp;
        swap(temp);
        swap(object);
    }
    return *this; 
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::Reference Signal<T,Allocator>::operator()(SizeType frame)
{
    return data_[frame];
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstReference Signal<T,Allocator>::operator()(SizeType frame) const
{
    return data_[frame];
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::Reference Signal<T,Allocator>::at(SizeType frame)
{
    if (frame < frames_)
        return data_[frame];
    else
        throw std::out_of_range("frame out of range!");
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstReference Signal<T,Allocator>::at(SizeType frame) const
{
    if (frame < frames_)
        return data_[frame];
    else
        throw std::out_of_range("frame out of range!");
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::resize(SizeType newFrames)
{
    if (newFrames == frames_)
    {
        return;
    }

    const SizeType newSize = newFrames;

    if (newSize == 0)
    {
        release();
        return;
    }

    Pointer newData = allocator_.allocate(newSize);

    if (data_ != nullptr)
    {
        const SizeType framesToCopy = std::min(frames_, newFrames);
        const SizeType sizeToCopy = framesToCopy;
        std::copy(data_, data_ + sizeToCopy, newData);

        allocator_.deallocate(data_, frames_);
    }

    data_ = newData;
    frames_ = newFrames;
    duration_ = (sampleRate_ > 0) ? static_cast<double>(frames_) / sampleRate_ : 0.0;
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::clear()
{
    fill(T(0));
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::release()
{
    if (data_ != nullptr)
    {
        allocator_.deallocate(data_,frames_);
        data_ = nullptr;
    }
    frames_ = 0;
    duration_ = 0.0;
}

template<typename T,typename Allocator>
void Signal<T,Allocator>::swap(Signal & second)
{
    std::swap(data_,second.data_);
    std::swap(frames_,second.frames_);
    std::swap(sampleRate_,second.sampleRate_);
    std::swap(duration_,second.duration_);
    std::swap(allocator_,second.allocator_);
}


template<typename T,typename Allocator>
void Signal<T,Allocator>::fill(const T & value)
{
    if (data_ != nullptr)
    {
        std::fill(data_,data_ + frames_,value);
    }
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::SignalIterator Signal<T,Allocator>::begin() noexcept
{
    return data_[0];
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::SignalIterator Signal<T,Allocator>::end() noexcept
{
    return data_[frames_ - 1];
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstSignalIterator Signal<T,Allocator>::cbegin() const noexcept
{
    return data_[0];
}

template<typename T,typename Allocator>
typename Signal<T,Allocator>::ConstSignalIterator Signal<T,Allocator>::cend() const noexcept
{
    return data_[frames_ - 1];
}

template<typename T,typename Allocator>
void swap(Signal<T,Allocator> & first,Signal<T,Allocator> & second) noexcept
{
    first.swap(second);
}


}