#pragma once
#include <cstddef>
#include <cstdint>
#include "sigflx_lib/sigflx_platform_allocator.h"

namespace SignumFlux
{
namespace Script
{
template<std::size_t BlockSize = 4096>
class ASTMemoryPool
{
    static_assert((BlockSize & (BlockSize - 1) == 0),"BlockSize Must be power of 2");
    static_assert((BlockSize >= 1024),"BlockSize too small! ");
public:
    using ByteType = std::uint8_t;
    using SizeType = std::size_t;
private:
    static constexpr std::size_t MinAllocSize = 16;  
    static constexpr std::size_t AlignmentSize = 64;     
    static constexpr std::size_t MaxLevel = 7;       
public:
    struct FreeNode
    {
        FreeNode * next;
    };

    template<std::size_t BlockSize>
    class PoolBlock
    {
    public:
        using ByteType = ASTMemoryPool::ByteType;
        using SizeType = ASTMemoryPool::SizeType;
    private:
        ByteType * data_ = nullptr;
        SizeType blockSize_ = 0;
        SizeType elementsCount_ = 0;
        SizeType elementsUsed_ = 0; 
        SizeType level_ = 0;
        FreeNode * freeList_ = nullptr;
        PoolBlock * next_ = nullptr;

        SizeType getElementSize() const;
        void initFreeList(SizeType elementSize);
    public:
        PoolBlock();
        PoolBlock(const PoolBlock & object) = delete;
        PoolBlock(PoolBlock && object);
        PoolBlock(SizeType level_);

        ~PoolBlock();

        PoolBlock & operator=(const PoolBlock & object) = delete;
        PoolBlock & operator=(PoolBlock && objcet);
        
        
    };

};
};
}