#pragma once

#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class K, class V>
class MutableMapEntry;

template <class K, class V>
class Shows<MutableMapEntry<K, V>> {
public:

  static constexpr bool exists = true;

  static const String Show(const MutableMapEntry<K, V>& entry) noexcept {
    return Shows<K>::Show(entry.ConstKey()) + String(": ") + Shows<V>::Show(entry.ConstValue());
  }

};

}