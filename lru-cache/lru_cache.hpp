#pragma once

#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

template <typename K, typename V>
class LRUCache
{
  public:
    LRUCache(size_t max_size);
    LRUCache(LRUCache&&) = default;
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(LRUCache&&) = default;
    LRUCache& operator=(const LRUCache&) = delete;
    ~LRUCache() = default;

    void set(const K& key, const V& value);
    std::optional<V> get(const K& key);

    using ListIterator = typename std::list<std::pair<K, V>>::iterator;

  private:
    size_t max_size;
    std::list<std::pair<K, V>> ls;
    std::unordered_map<K, ListIterator> mp;
};

template <typename K, typename V>
LRUCache<K, V>::LRUCache(size_t max_size) : max_size(max_size)
{
}

template <typename K, typename V>
void LRUCache<K, V>::set(const K& key, const V& value)
{
    if (ls.size() == max_size)
    {
        std::pair<K, V> node = ls.back();
        ls.pop_back();
        K lastKey = node.first;
        mp.erase(lastKey);
    }

    if (mp.find(key) != mp.end())
    {
        ListIterator node = mp[key];
        ls.erase(node);
        mp.erase(key);
    }

    ls.push_front({key, value});
    mp[key] = ls.begin();
}

template <typename K, typename V>
std::optional<V> LRUCache<K, V>::get(const K& key)
{
    auto nodeIt = mp.find(key);

    if (nodeIt == mp.end())
    {
        return std::nullopt;
    }

    auto node = nodeIt->second;
    V value = node->second;
    ls.erase(node);

    ls.push_front({key, value});
    mp[key] = ls.begin();

    return value;
}
