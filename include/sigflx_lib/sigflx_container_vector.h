#pragma once
#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include "sigflx_lib/sigflx_allocators_aligned.h"

namespace SignumFlux
{
namespace Container
{
template<typename T,typename Allocator = Allocators::AlignedAllocator<T>>
class Vector
{
public:
    using ValueType = T;
    using SizeType = std::size_t;
    using Pointer = T *;
    using ConstPointer = const T *;
    using Reference = T &;
    using ConstReference = const T &;
    using Iterator = Pointer;
    using ConstIterator = ConstPointer;
    using AllocatorType = Allocator;
private:
    Pointer data_ = nullptr;
    SizeType size_ = 0;
    SizeType capacity_ = 0;
    AllocatorType allocator_;
    
public:
    Vector();
    explicit Vector(const AllocatorType & allocator);
    Vector(const Vector & object);
    Vector(const Vector & object,const AllocatorType & allocator);
    Vector(Vector && object) noexcept;
    Vector(std::initializer_list<ValueType> list);
    Vector(std::initializer_list<ValueType> list,const AllocatorType & allocator);
    Vector(SizeType size);
    Vector(SizeType size, const Allocator & allocator);
    Vector(SizeType size,ValueType value = ValueType(0));
    Vector(SizeType size,ValueType value,const AllocatorType & allocator);

    ~Vector();

    Pointer data() noexcept { return data_; };
    ConstPointer data() const noexcept { return data_; };
    SizeType size() const noexcept { return size_; };
    SizeType capacity() const noexcept { return capacity_; };
    bool empty() const noexcept { return size_ == 0; };

    Vector & operator=(const Vector & object);
    Vector & operator=(Vector && object) noexcept;

    Reference operator[](SizeType index);
    ConstReference operator[](SizeType index) const;
    Reference at(SizeType index);
    ConstReference at(SizeType index) const;
    Reference front();
    ConstReference front() const;
    Reference back();
    ConstReference back() const;

    void clear();
    void fill(ValueType value = ValueType(0));
    void resize(SizeType n);
    void reserve(SizeType n);
    void shrinkToFit();
    void pushBack(ValueType value);
    void popBack();

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

    void swap(Vector & object) noexcept;
};
}
}

#include "../../src/sigflx_lib/sigflx_container_vector.tpp"