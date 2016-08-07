#pragma once

#include <everest/containers/map.h>
#include <everest/traits/unlawful/>

namespace everest {

template <class K, class V>
class Map;

template <class K, class V>
class Container<Map<K, V>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Map<K, V>& map) noexcept {
    return map.Length();
  }

  static bool IsEmpty(const Map<K, V>& map) noexcept {
    return map.IsEmpty();
  }

};

}