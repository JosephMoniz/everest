#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class MutableRemove<MutableMap<K, V>> {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V>& RemoveInPlace(const K& key, MutableMap<K, V>& map) noexcept {
    auto bucket = map.GetAllocatedBucket(key);
    map.RedactBucketSize(bucket);
    FilterInPlace([&](MutableMapEntry<K, V>& entry) { return entry.Key() != key; }, *bucket);
    map.AddBucketSize(bucket);
    return map;
  }

  static MutableMap<K, V>& RemoveInPlace(const MutableMap<K, V>& source, MutableMap<K, V>& map) noexcept {
    ForEach(source, [&](MutableMapEntry<K, V>& entry) {
      RemoveInPlace(entry.Key(), map);
    });
    return map;
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  static MutableMap<K, V>& RemoveInPlace(const U& source, MutableMap<K, V>& map) noexcept {
    ForEach(source, [&](const K& item) {
      RemoveInPlace(item, map);
    });
    return map;
  }

};

}