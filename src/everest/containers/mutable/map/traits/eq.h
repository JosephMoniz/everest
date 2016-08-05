#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Eq<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableMap<K, V>& lhs, const MutableMap<K, V>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}