#pragma once

#include <everest/mutable_containers/mutable_map.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Semigroup<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V> Add(const MutableMap<K, V>& lhs, const MutableMap<K, V>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}