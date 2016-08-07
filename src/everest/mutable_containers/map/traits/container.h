#pragma once

#include <everest/mutable_containers/mutable_map.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template<class K, class V>
class MutableMap;

template <class K, class V>
class Container<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableMap<K, V>& map) noexcept {
    return map.Length();
  }

  static bool IsEmpty(const MutableMap<K, V>& map) noexcept {
    return map.IsEmpty();
  }

};

}