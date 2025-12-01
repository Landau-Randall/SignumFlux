#pragma once
#include <cstddef>
#include <stdexcept>


namespace SignumFlux
{
namespace Container
{
template<typename T>
class VectorView
{
public:
    using ValueType = T;
    using SizeType = std::size_t;
    using Pointer = const T *;
    using ConstPointer = const T *;
    using Iterator = ConstPointer;
    using ConstIterator = ConstPointer;
    using Reference = const T &;
    using ConstReference = const T &;
private:
    ConstPointer data_ = nullptr;
    SizeType size_ = 0;
public:
    VectorView() = default;
    VectorView(const VectorView & object) = default;
    VectorView(VectorView && object) noexcept = default;
    VectorView(ConstPointer data,SizeType size);

    ~VectorView() = default;

    VectorView & operator=(const VectorView & object) = default;
    VectorView & operator=(VectorView && object) = default;

    Pointer data() noexcept { return data_; };
    ConstPointer data() const noexcept { return data_; };
    SizeType size() const noexcept { return size_; };

    Reference operator[](SizeType index);
    ConstReference operator[](SizeType index) const;
    Reference at(SizeType index);
    ConstReference at(SizeType index) const;

    VectorView subView(std::size_t start,std::size_t size) const;

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;

};
}
}

#include "../../src/sigflx_lib/sigflx_container_vector_view.tpp"