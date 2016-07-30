#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/containers/mutable/map/mutable_map_entry.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class MutableMapEntry;

template <class K, class V>
class Shows<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableMap<K, V>& map) noexcept {
    auto out = String("MutableMap(");
    ForEach(map, [&](const MutableMapEntry<K, V>& entry) {
      out = std::move(out) + Shows<MutableMapEntry<K, V>>::Show(entry) + String(", ");
    });
    return Take(out.Length() - 2, std::move(out)) + String(")");
  }

};

}