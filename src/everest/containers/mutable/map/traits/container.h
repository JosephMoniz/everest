#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class K, class V>
class MutableMap;

template <class K, class V>
class Container<MutableMap<K, V>> {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const MutableMap<K, V>& map) noexcept {
    return map._size;
  }

  static constexpr bool IsEmpty(const MutableMap<K, V>& map) noexcept {
    return map._size == 0;
  }

};

}