#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/associative.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Associative<MutableMap<K, V>> {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V> Put(K&& key, V&& value, MutableMap<K, V>& container) noexcept {
    auto copy = Copy(container);
    return PutInPlace(std::move(key), std::move(value), copy);
  }

  static MutableMap<K, V> Put(MutableMap<K, V>&& source, MutableMap<K, V>& container) noexcept {
    auto copy = Copy(container);
    ForEach(source, [&](MutableMapEntry<K, V>& entry) {
      PutInPlace(std::move(entry.Key()), std::move(entry.Value()), copy);
    });
    return copy;
  }

  static const V* Get(const K& key, MutableMap<K, V>& container) noexcept {
    auto bucket = container.GetBucket(key);
    auto entry  = FindInPlace([&](auto e){ return e.Key() == key; }, *bucket);
    return entry == nullptr
      ? nullptr
      : &entry->Value();
  };

};

}