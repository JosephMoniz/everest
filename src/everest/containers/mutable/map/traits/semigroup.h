#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Semigroup<MutableMap<K, V>> {
public:

  static constexpr bool exists = true;

  static constexpr MutableMap<K, V> Add(const MutableMap<K, V>& lhs, const MutableMap<K, V>& rhs) noexcept {
    auto results = MutableMap<K, V>();
    ForEach(lhs, [&](MutableMapEntry<K, V>& entry) {
      PutInPlace(Copy(entry.Key()), Copy(entry.Value()), results);
    });
    ForEach(rhs, [&](MutableMapEntry<K, V>& entry) {
      auto matched = GetInPlace(entry.Key(), results);
      if (matched == nullptr) {
        PutInPlace(Copy(entry.Key()), Copy(entry.Value()), results);
      } else {
        PutInPlace(Copy(entry.Key()), *matched + entry.Value(), results);
      }
    });
    return results;
  }

};

}