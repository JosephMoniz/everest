#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Copyable<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V> Copy(const MutableMap<K, V>& map) noexcept {
    return map.Copy();
  }

};

}