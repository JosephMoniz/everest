#pragma once

#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class K, class V>
class MutableMapEntry;

template<class K, class V>
class Eq<MutableMapEntry<K, V>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableMapEntry<K, V>& lhs, const MutableMapEntry<K, V>& rhs) noexcept {
    return Eq<K>::Equals(lhs.ConstKey(), rhs.ConstKey());
  }

  static bool Equals(const K& lhs, const MutableMapEntry<K, V>& rhs) noexcept {
    return Eq<K>::Equals(lhs, rhs.ConstKey());
  }

  static bool Equals(const MutableMapEntry<K, V>& lhs, const K& rhs) noexcept {
    return Eq<K>::Equals(lhs.ConstKey(), rhs);
  }

};

}