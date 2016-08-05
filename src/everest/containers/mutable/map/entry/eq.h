#pragma once

#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class K, class V>
class MutableMapEntry;

template<class K, class V>
class Eq<MutableMapEntry<K, V>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableMapEntry<K, V>& lhs, const MutableMapEntry<K, V>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

  static bool Equals(const K& lhs, const MutableMapEntry<K, V>& rhs) noexcept {
    return rhs.Equals(lhs);
  }

  static bool Equals(const MutableMapEntry<K, V>& lhs, const K& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}