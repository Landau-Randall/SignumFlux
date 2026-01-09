#include "sigflx_lib/sigflx_allocators_fixed_pool.h"


namespace SignumFlux
{
namespace Allocators
{

template<FixedBlockPool::SizeType BlockSize>
FixedBlockPool::PoolBlock<BlockSize>::PoolBlock()
{

}

template<FixedBlockPool::SizeType BlockSize>
FixedBlockPool::PoolBlock<BlockSize>::PoolBlock(ByteType * source,SizeType blockSize)
{
    assert(is2Power(blockSize));
    blockSize_ = blockSize;
    blockCount_ = BlockSize / blockSize_;
    freeCount_  = blockCount_;
    data_ = source;
    void * ptr = Platform::Allocate<Platform::CurrentOS>::allocate(freeCount_ * sizeof(ByteType*),64);
    if (ptr != nullptr)
    {
        freeList_ = static_cast<ByteType**>(ptr);
    }
    for (SizeType i = 0;i < blockCount_;i++)
    {
        freeList_[i] = (data_ + i * blockSize_);
    }
}

template<FixedBlockPool::SizeType BlockSize>
FixedBlockPool::PoolBlock<BlockSize>::PoolBlock(PoolBlock && object):
data_(object.data_),
freeList_(object.freeList_),
blockSize_(object.blockSize_),
blockCount_(object.blockCount_),
freeCount_(object.freeCount_)
{
    object.data_ = nullptr;
    object.freeList_ = nullptr;
    object.blockSize_ = 0;
    object.blockCount_ = 0;
    object.freeCount_ = 0;
}

template<FixedBlockPool::SizeType BlockSize>
FixedBlockPool::PoolBlock<BlockSize>::~PoolBlock()
{

}

template<FixedBlockPool::SizeType BlockSize>
FixedBlockPool::PoolBlock<BlockSize> & FixedBlockPool::PoolBlock<BlockSize>::operator=(PoolBlock && object)
{
    if (this != &object)
    {
        data_ = object.data_;
        freeList_ = object.freeList_;
        blockSize_ = object.blockSize_;
        blockCount_ = object.blockCount_;
        freeCount_ = object.freeCount_;

        object.data_ = nullptr;
        object.freeList_ = nullptr;
        object.blockSize_ = 0;
        object.blockCount_ = 0;
        object.freeCount_ = 0;
    }
    return *this;
}

template<FixedBlockPool::SizeType BlockSize>
void * FixedBlockPool::PoolBlock<BlockSize>::allocateBlock()
{
    if (freeCount_ == 0)
    {
        return nullptr;
    }
    else
    {
        return freeList_[--freeCount_];
    }
}

template<FixedBlockPool::SizeType BlockSize>
void FixedBlockPool::PoolBlock<BlockSize>::deallocateBlock(void * ptr)
{
    freeList_[freeCount_++] = static_cast<ByteType*>(ptr);
}

template<FixedBlockPool::SizeType BlockSize>
void FixedBlockPool::PoolBlock<BlockSize>::release()
{
    data_ = nullptr;
    if (freeList_ != nullptr)
    {
        Platform::DeAllocator<Platform::CurrentOS>::deallocate(freeList_);
    }
    freeList_ = nullptr;
    blockSize_ = 0;
    blockCount_ = 0;
    freeCount_ = 0;
}

template<FixedBlockPool::SizeType BlockSize>
bool FixedBlockPool::PoolBlock<BlockSize>::isFree(SizeType n) const noexcept
{
    return freeCount_ >= n;
}

FixedBlockPool::SizeType FixedBlockPool::nextPowerOfTwo(SizeType x)
{
    if (x == 0)
        return 1;
        --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

FixedBlockPool::FixedBlockPool()
{
    void * ptr = Platform::Allocate<Platform::CurrentOS>::allocate(7 * BlockSize_,64);
    if (ptr != nullptr)
    {
        source_ = static_cast<ByteType*>(ptr);
        for (SizeType i = 0;i < 7;i++)
        {
            pool_[i] = PoolBlock<BlockSize_>(source_ + i * BlockSize_, static_cast<PoolBlock<BlockSize_>::SizeType>(1 << i));
        }
    }
}

FixedBlockPool::~FixedBlockPool()
{
    for (SizeType i = 0;i < 7;i++)
    {
        pool_[i].release();
    }
    Platform::DeAllocator<Platform::CurrentOS>::deallocate(source_);
    source_ = nullptr;
}

template<typename T>
T * FixedBlockPool::allocate(SizeType n)
{
    assert(n == 1);
    SizeType byteNumber = sizeof(T);
    float level = std::log2(byteNumber);
    SizeType near = static_cast<SizeType>(std::ceil(level));
    return static_cast<T*>(pool_[near].allocateBlock()); 
}

template<typename T>
void FixedBlockPool::deallocate(T * ptr,SizeType n)
{
    assert(n == 1);
    SizeType byteNumber = sizeof(T);
    float level = std::log2(byteNumber);
    SizeType near = static_cast<SizeType>(std::ceil(level));
    pool_[near].deallocateBlock(ptr);
}


template<typename T>
typename FixedPoolAllocator<T>::Pointer FixedPoolAllocator<T>::allocate(SizeType n)
{
    if (n == 0)
    {
        return nullptr;
    }
    return FixedBlockPool::instance().allocate<T>(n);
}

template<typename T>
void FixedPoolAllocator<T>::deallocate(Pointer ptr,SizeType n)
{
    return FixedBlockPool::instance().deallocate(ptr,n);
}

}
}