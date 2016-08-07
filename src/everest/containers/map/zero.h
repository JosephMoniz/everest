#pragma once

#include <everest/containers/map.h>
#include <everest/traits/unlawful/>

namespace everest {

template <class K, class V>
class Map;

template<class K, class V>
class ZeroVal<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static Map<K, V> Zero() noexcept {
    return Map<K, V>::Zero();
  }

};

}