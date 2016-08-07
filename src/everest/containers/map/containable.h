#pragma once

#include <everest/containers/map.h>
#include <everest/traits/unlawful/>

namespace everest {

template <class K, class V>
class Map;

template<class K, class V>
class Containable<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const K& key, const Map<K, V>& map) noexcept {
    return map.Contains(key);
  }

};

}