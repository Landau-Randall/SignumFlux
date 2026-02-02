#include "sigflx_lib/sigflx_container_vector_view.h"

namespace SignumFlux
{
namespace Container
{
template<typename T>
VectorView<T>::VectorView(Pointer data,SizeType size):
data_(data),
size_(size)
{

}

template<typename T>
typename VectorView<T>::Reference VectorView<T>::operator[](SizeType index)
{
    return data_[index];
}

template<typename T>
typename VectorView<T>::Reference VectorView<T>::at(SizeType index)
{
    if (index < size_)
    {
        return data_[index];
    }
    else
    {
        throw std::out_of_range("index out of vector view range!\n");
    }
}

template<typename T>
typename VectorView<T>::Iterator VectorView<T>::begin()
{
    return data_;
}

template<typename T>
typename VectorView<T>::Iterator VectorView<T>::end()
{
    return data_ + size_;
}

}
}