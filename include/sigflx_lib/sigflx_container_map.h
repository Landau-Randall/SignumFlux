#pragma once
#include <cstddef>
#include <cstdint>
#include "sigflx_lib/sigflx_math_hasher.h" 

namespace SignumFlux
{
namespace Container
{
template<typename T1,typename T2>
struct Pair
{
    T1 first;
    T2 second;

    Pair() = default;
    Pair(const Pair & object) = default;
    Pair(Pair && object) = default;
    Pair(const T1 & f,const T2 & s) : first(f), second(s) {};

    ~Pair() = default;

    Pair & operator=(const Pair & object) = default;
    Pair & operator=(Pair && object) = default;
};

template<typename Key,typename Value>
struct MapNode
{
    Pair<Key,Value> data_;
    MapNode * next_ = nullptr;

    MapNode(const Key & k,const Value & v) : data_(k,v) {};
};

template<typename Key,typename Value>
class Map
{
public:
    using SizeType = std::size_t;
private:
    MapNode<Key,Value> ** buckets_ = nullptr;
    SizeType bucketsNumber_ = 0;
public:
    Map();
    Map(const Map & object) = delete;
    Map(Map && object);
    Map(SizeType bucketsNumber);
    ~Map();

    Map & operator=(const Map & object) = delete;
    Map & operator=(Map && object);

    void insert(const Key & key, const Value & value);
    const Value * find(const Key & key) const;

    SizeType size() const noexcept { return bucketsNumber_; };
};
}
}

#include "../../src/sigflx_lib/sigflx_container_map.tpp"