#include "lru_cache.hpp"
#include <cstddef>
#include <iostream>
#include <string>

constexpr size_t MAX_CACHE_SIZE = 5;

int main()
{
    LRUCache<std::string, int> cache(MAX_CACHE_SIZE);

    cache.set("diksha", 1);
    cache.set("deepanshu", 2);
    cache.set("papa", 3);
    cache.set("dulari", 4);
    cache.set("sammu", 5);
    cache.set("mummy", 6);

    auto cachedValue = cache.get("diksha");

    if (cachedValue.has_value())
    {
        std::cout << cachedValue.value() << "\n";
    }

    return 0;
}
