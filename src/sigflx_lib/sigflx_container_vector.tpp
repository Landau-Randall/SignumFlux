#include "sigflx_lib/sigflx_container_vector.h"

namespace SignumFlux
{
namespace Container
{
template<typename T,typename Allocator>
Vector<T,Allocator>::Vector()
{

}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(const AllocatorType & allocator):
allocator_(allocator)
{

}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(const Vector & object):
size_(object.size_),
capacity_(object.capacity_),
allocator_(object.allocator_)
{
    if (object.data_ != nullptr)
    {
        data_ = allocator_.allocate(capacity_);
        std::copy(object.data_,object.data_ + size_,data_);
    }
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(const Vector & object,const AllocatorType & allocator):
size_(object.size_),
capacity_(object.capacity_),
allocator_(allocator)
{
    if (object.data_ != nullptr)
    {
        data_ = allocator_.allocate(capacity_);
        std::copy(object.data_,object.data_ + size_,data_);
    }
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(Vector && object) noexcept:
data_(object.data_),
size_(object.size_),
capacity_(object.capacity_),
allocator_(std::move(object.allocator_))
{
    object.data_ = nullptr;
    object.size_ = 0;
    object.capacity_ = 0;
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(std::initializer_list<ValueType> list):
allocator_()
{
    if (list.size() != 0)
    {
        size_ = list.size();
        capacity_ = 2 * size_;
        data_ = allocator_.allocate(capacity_);
        std::copy(list.begin(),list.end(),data_);
    }
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(std::initializer_list<ValueType> list,const AllocatorType & allocator):
allocator_(allocator)
{
    if (list.size() != 0)
    {
        size_ = list.size();
        capacity_ = 2 * size_;
        data_ = allocator_.allocate(capacity_);
        std::copy(list.begin(),list.end(),data_);
    }
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(SizeType size):
size_(size),
capacity_(size * 2),
allocator_()
{
    data_ = allocator_.allocate(capacity_);
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(SizeType size,const AllocatorType & allocator):
size_(size),
capacity_(size * 2),
allocator_(allocator)
{
    data_ = allocator_.allocate(capacity_);
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(SizeType size,ValueType value):
size_(size),
capacity_(size * 2),
allocator_()
{
    data_ = allocator_.allocate(capacity_);
    if (data_ != nullptr)
    {
        for (SizeType i = 0;i < size_;++i)
        {
            data_[i] = value;
        }
    }
}

template<typename T,typename Allocator>
Vector<T,Allocator>::Vector(SizeType size,ValueType value,const AllocatorType & allocator):
size_(size),
capacity_(size * 2),
allocator_(allocator)
{
    data_ = allocator_.allocate(capacity_);
    if (data_ != nullptr)
    {
        for (SizeType i = 0;i < size_;++i)
        {
            data_[i] = value;
        }
    }
}

template<typename T,typename Allocator>
Vector<T,Allocator>::~Vector()
{
    if (data_ != nullptr)
    {
        allocator_.deallocate(data_,capacity_);
    }
    size_ = 0;
    capacity_ = 0;
}

template<typename T,typename Allocator>
Vector<T,Allocator> & Vector<T,Allocator>::operator=(const Vector & object)
{
    Vector temp(object);
    swap(temp);
    return *this;
}

template<typename T,typename Allocator>
Vector<T,Allocator> & Vector<T,Allocator>::operator=(Vector && object) noexcept
{
    if (this != &object)
    {
        Vector temp;
        swap(temp);
        swap(object);
    }
    return *this;
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::Reference Vector<T,Allocator>::operator[](SizeType index)
{
    return data_[index];
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::ConstReference Vector<T,Allocator>::operator[](SizeType index) const
{
    return data_[index];
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::Reference Vector<T,Allocator>::at(SizeType index)
{
    if (index < size_)
    {
        return data_[index];
    }
    else
    {
        throw std::out_of_range("vector index out of range!\n");
    }
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::ConstReference Vector<T,Allocator>::at(SizeType index) const
{
    if (index < size_)
    {
        return data_[index];
    }
    else
    {
        throw std::out_of_range("vector index out of range!\n");
    }
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::Reference Vector<T,Allocator>::front()
{
    return data_[0];
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::ConstReference Vector<T,Allocator>::front() const
{
    return data_[0];
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::Reference Vector<T,Allocator>::back()
{
    return data_[size_ - 1];
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::ConstReference Vector<T,Allocator>::back() const
{
    return data_[size_ - 1];
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::clear()
{
    size_ = 0;
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::resize(SizeType n)
{
    if (n == size_)
    {
        return;
    }

    if (data_ != nullptr)
        {
        if (n <= capacity_)
        {
            if(n > size_)
            {
                std::fill(data_ + size_,data_ + n,ValueType(0));
            }
            size_ = n;

        }
        else
        {
            Pointer newData = allocator_.allocate(n * 2);
            std::copy(data_,data_ + size_,newData);
            allocator_.deallocate(data_,capacity_);
            data_ = newData;
            size_ = n;
            capacity_ = 2 * n;
        }
    }
    else
    {
        capacity_ = 2 * n;
        data_ = allocator_.allocate(capacity_);
        size_ = n;
    }
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::reserve(SizeType n)
{
    if (n > capacity_)
    {
        Pointer newData = allocator_.allocate(n);
        if (data_ != nullptr)
        {
            std::copy(data_,data_ + size_,newData);
            allocator_.deallocate(data_,capacity_);
        }
        data_ = newData;
        capacity_ = n;
    }
    else
    {
        return ;
    }
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::shrinkToFit()
{
    if (size_ == capacity_)
    {
        return ;
    }

    Pointer newData = allocator_.allocate(size_);
    if (data_ != nullptr)
    {
        std::copy(data_,data_ + size_,newData);
        allocator_.deallocate(data_,capacity_);
    }
    data_ = newData;
    capacity_ = size_;
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::fill(ValueType value)
{
    std::fill(data_,data_ + size_,value);
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::pushBack(ValueType value)
{
    if (size_ + 1 <= capacity_)
    {
        if (data_ != nullptr)
        {
            data_[size_++] = value;
        }
    }
    else
    {
        Pointer newData = allocator_.allocate(capacity_ == 0 ? 1 : 2 * capacity_);
        if (data_ != nullptr)
        {
            std::copy(data_,data_ + size_,newData);
            allocator_.deallocate(data_,capacity_);
        }
        data_ = newData;
        data_[size_++] = value;
        capacity_ *= 2;
    }
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::popBack()
{
    if (!empty())
    {
        --size_;
    }
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::Iterator Vector<T,Allocator>::begin()
{
    return data_;
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::Iterator Vector<T,Allocator>::end()
{
    return data_ + size_;
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::ConstIterator Vector<T,Allocator>::cbegin() const
{
    return data_;
}

template<typename T,typename Allocator>
typename Vector<T,Allocator>::ConstIterator Vector<T,Allocator>::cend() const
{
    return data_ + size_;
}

template<typename T,typename Allocator>
void Vector<T,Allocator>::swap(Vector & object) noexcept
{
    std::swap(data_,object.data_);
    std::swap(size_,object.size_);
    std::swap(capacity_,object.capacity_);
    std::swap(allocator_,object.allocator_);
}


}
}