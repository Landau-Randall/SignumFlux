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
    using Pointer = T *;
    using Iterator = Pointer;
    using Reference = T &;
private:
    Pointer data_ = nullptr;
    SizeType size_ = 0;
public:
    VectorView() = default;
    VectorView(const VectorView & object) = default;
    VectorView(VectorView && object) noexcept = default;
    VectorView(Pointer data,SizeType size);

    ~VectorView() = default;

    VectorView & operator=(const VectorView & object) = default;
    VectorView & operator=(VectorView && object) = default;

    Pointer data() noexcept { return data_; };
    SizeType size() const noexcept { return size_; };

    Reference operator[](SizeType index);
    Reference at(SizeType index);

    Iterator begin();
    Iterator end();

};
}
}

#include "../../src/sigflx_lib/sigflx_container_vector_view.tpp"