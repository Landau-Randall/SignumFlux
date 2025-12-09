#include "sigflx_lib/sigflx_container_map.h"

namespace SignumFlux
{
namespace Container
{
template<typename Key,typename Value>
Map<Key,Value>::Map()
{

}

template<typename Key,typename Value>
Map<Key,Value>::Map(Map && object):
buckets_(object.buckets_),
bucketsNumber_(object.bucketsNumber_)
{
    object.buckets_ = nullptr;
    object.bucketsNumber_ = 0;
}

template<typename Key,typename Value>
Map<Key,Value>::Map(SizeType bucketsNumber)
{
    bucketsNumber_ = 1;
    while (bucketsNumber_ < bucketsNumber) 
    {
        bucketsNumber_ <<= 1; 
    }
    buckets_ = new MapNode<Key,Value> * [bucketsNumber_];
}

template<typename Key,typename Value>
Map<Key,Value>::~Map()
{
    for (std::size_t i = 0;i < bucketsNumber_;++i)
    {
        MapNode<Key,Value> * node = buckets_[i];
        while (node != nullptr)
        {
            MapNode<Key,Value>* nextNode = node->next_;
            delete node;
            node = nextNode;
        }
    }

    if (buckets_ != nullptr)
    {
        delete [] buckets_;
        buckets_ = nullptr;
    }
    bucketsNumber_ = 0;
}

template<typename Key,typename Value>
Map<Key,Value> & Map<Key,Value>::operator=(Map && object)
{
    if (this != &object)
    {
        if (buckets_ != nullptr)
        {
            delete [] buckets_;
        }
        buckets_ = object.buckets_;
        bucketsNumber_ = object.bucketsNumber_;

        object.buckets_ = nullptr;
        object.bucketsNumber_ =  0;
    }
    return *this;
}

template<typename Key,typename Value>
void Map<Key,Value>::insert(const Key & key, const Value & value)
{
    if (buckets_ != nullptr && bucketsNumber_ != 0)
    {
        SizeType hash = Math::viewHash<Key,SizeType>(key);
        SizeType mod = hash & (bucketsNumber_ - 1);
        MapNode<Key,Value> * node = buckets_[mod];

        if (node != nullptr)
        {
            while (node != nullptr)
            {
                if (key == node->data_.first)
                {
                    node->data_.second = value;
                    return;
                }
                node = node->next_;
            }
        }
        else
        {
            buckets_[mod] = new MapNode<Key,Value>(key,value);
            buckets_[mod]->next_ = nullptr;
            return;
        }

        MapNode<Key,Value> * newNode = new MapNode<Key,Value>(key, value);
        newNode->next_ = buckets_[mod];
        buckets_[mod] = newNode;

    }
}

template<typename Key,typename Value>
const Value * Map<Key,Value>::find(const Key & key) const
{
    if (buckets_ != nullptr && bucketsNumber_ != 0)
    {
        SizeType hash = Math::viewHash<Key,SizeType>(key);
        SizeType mod = hash & (bucketsNumber_ - 1);
        MapNode<Key,Value> * node = buckets_[mod];
        
        while (node != nullptr)
        {
            if (key == node->data_.first)
            {
                return &node->data_.second;
            }
            node = node->next_;
        }
    }
    return nullptr;
}
}
}
