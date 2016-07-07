#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class ZeroVal<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static constexpr MutableMap<K, V> Zero() noexcept {
    return MutableMap<K, V>();
  }

};

}