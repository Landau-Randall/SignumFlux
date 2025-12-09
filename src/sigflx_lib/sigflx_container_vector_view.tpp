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
bool VectorView<T>::operator==(const VectorView & object) const
{
    if (size_ != object.size_)
    {
        return false;
    }
    else
    {
        for (SizeType i = 0;i < size_;++i)
        {
            if (data_[i] != object.data_[i])
                return false;
        }
        return true;
    }
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
typename VectorView<T>::ConstReference VectorView<T>::at(SizeType index) const
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
VectorView<T> VectorView<T>::subView(std::size_t start,std::size_t size) const
{
    if (start <= size_ && size <= size_ - start)
    {
        return VectorView(data_ + start,size);
    }
    else
    {
        return VectorView();
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