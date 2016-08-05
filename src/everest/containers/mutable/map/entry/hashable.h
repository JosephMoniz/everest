#pragma once

#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/traits/unlawful/hashable.h>

namespace everest {

template <class K, class V>
class MutableMapEntry;

template <class K, class V>
class Hashable<MutableMapEntry<K, V>> final {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const MutableMapEntry<K, V>& entry) noexcept {
    return Hashable<K>::Hash(entry.ConstKey());
  }

};

}