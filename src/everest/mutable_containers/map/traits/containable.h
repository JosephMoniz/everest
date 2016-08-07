#pragma once

#include <everest/mutable_containers/mutable_map.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Containable<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const K& key, const MutableMap<K, V>& map) noexcept {
    return map.Contains(key);
  }

};

}