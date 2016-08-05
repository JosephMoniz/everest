#pragma once

#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/traits/unlawful/ord.h>

namespace everest {

template <class K, class V>
class MutableMapEntry;

template <class K, class V>
class Ord<MutableMapEntry<K, V>> final {
public:

  static constexpr bool exists = true;

  static Ordering Compare(const MutableMapEntry<K, V>& lhs, const MutableMapEntry<K, V>& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static Ordering Compare(const MutableMapEntry<K, V>& lhs, const K& rhs) noexcept {
    return lhs.Compare(rhs);
  }

  static const MutableMapEntry<K, V>& Min(const MutableMapEntry<K, V>& lhs, const MutableMapEntry<K, V>& rhs) noexcept {
    return lhs.Min(rhs);
  }

  static const MutableMapEntry<K, V>& Max(const MutableMapEntry<K, V>& lhs, const MutableMapEntry<K, V> rhs) noexcept {
    return lhs.Max(rhs);
  }

};

}