#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_associative.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class MutableAssociative<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V>& PutInPlace(K&& key, V&& value, MutableMap<K, V>& container) noexcept {
    auto bucket = container.GetAllocatedBucket(key);
    container.RedactBucketSize(bucket);
    FilterInPlace([&](auto& e){ return e.Key() != key; }, *bucket);
    PushInPlace(MutableMapEntry<K, V>(std::move(key), std::move(value)), *bucket);
    container.AddBucketSize(bucket);
    return container.ResizeIfNecessary();
  }

  static MutableMap<K, V>& PutInPlace(MutableMap<K, V>&& source, MutableMap<K, V>& container) noexcept {
    ForEach(source, [&](MutableMapEntry<K, V>& entry) {
      PutInPlace(std::move(entry.Key()), std::move(entry.Value()), container);
    });
  }

  static V* GetInPlace(const K& key, MutableMap<K, V>& container) noexcept {
    auto bucket = container.GetBucket(key);
    auto entry  = FindInPlace([&](auto& e){ return e.Key() == key; }, *bucket);
    return entry == nullptr
      ? nullptr
      : &entry->Value();
  };

};

}