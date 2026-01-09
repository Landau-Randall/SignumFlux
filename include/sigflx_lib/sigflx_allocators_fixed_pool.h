#pragma once
#include <cstddef>
#include <cassert>
#include <cmath>
#include "sigflx_lib/sigflx_platform_allocator.h"

namespace SignumFlux
{
namespace Allocators
{
class FixedBlockPool
{
public:
    using SizeType = std::size_t;
    using ByteType = unsigned char;
    template<SizeType BlockSize>
    class PoolBlock
    {
        static_assert((BlockSize ^ (BlockSize - 1) == 0) && (BlockSize > 64),"BlockSize must be the power of 2!");
    public:
        using SizeType = FixedBlockPool::SizeType;
        using ByteType = FixedBlockPool::ByteType;
    private:
        ByteType * data_ = nullptr;
        ByteType ** freeList_ = nullptr;
        SizeType blockSize_ = 0;
        SizeType blockCount_ = 0;
        SizeType freeCount_ = 0;
        bool is2Power(SizeType number) { return (number != 0) && ((number) & (number - 1)) == 0; };
    public:
        PoolBlock();
        PoolBlock(ByteType * source,SizeType blockSize);
        PoolBlock(const PoolBlock & object) = delete;
        PoolBlock(PoolBlock && object);

        ~PoolBlock();

        PoolBlock & operator=(const PoolBlock & object) = delete;
        PoolBlock & operator=(PoolBlock && objcet);

        SizeType blockSize() const noexcept { return blockSize_; };
        SizeType freeCount() const noexcept { return freeCount_; };

        void * allocateBlock();
        void deallocateBlock(void * ptr);
        void release();

        bool isEmpty() const noexcept { return  (blockCount_ != 0) && (freeCount_ == blockCount_); };
        bool isFree(SizeType n) const noexcept;
    };
private:
    static constexpr SizeType BlockSize_ = 4096;
    ByteType * source_ = nullptr;
    PoolBlock<BlockSize_> pool_[7];
    SizeType nextPowerOfTwo(SizeType x);
public:
    FixedBlockPool();
    FixedBlockPool(const FixedBlockPool & object) = delete;
    FixedBlockPool(FixedBlockPool && object) = delete;

    ~FixedBlockPool();

    FixedBlockPool & operator=(const FixedBlockPool & object) = delete;
    FixedBlockPool & operator=(FixedBlockPool && object) = delete;


    template<typename T>
    T * allocate(SizeType n = 1);

    template<typename T>
    void deallocate(T * pointer,SizeType n = 1);

    static FixedBlockPool& instance()
    {
        static FixedBlockPool pool;
        return pool;
    }
};


template<typename T>
class FixedPoolAllocator
{
public:
    using ValueType = T;
    using Pointer = T*;
    using SizeType = std::size_t;
public:
    FixedPoolAllocator() noexcept = default;
    Pointer allocate(SizeType n);
    void deallocate(Pointer ptr,SizeType n);
};

}
}

#include "../../src/sigflx_lib/sigflx_allocators_fixed_pool.tpp"