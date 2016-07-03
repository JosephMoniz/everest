#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Containable<MutableMap<K, V>> {
public:

  static constexpr bool exists = true;

  static constexpr bool Contains(const K& key, const MutableMap<K, V>& map) noexcept {
    return Any([&](const MutableMapEntry<K, V>& e){ return e.ConstKey() == key; }, *map.GetConstBucket(key));
  }

};

}