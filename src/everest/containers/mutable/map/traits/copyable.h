#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Copyable<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V> Copy(const MutableMap<K, V>& map) noexcept {
    auto copy = MutableMap<K, V>();
    ForEach(map, [&](MutableMapEntry<K, V>& entry) {
      PutInPlace(Copyable<K>::Copy(entry.Key()), Copyable<V>::Copy(entry.Value()), copy);
    });
    return copy;
  }

};

}