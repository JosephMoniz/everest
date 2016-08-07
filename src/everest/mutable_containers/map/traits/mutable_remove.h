#pragma once

#include <everest/mutable_containers/mutable_map.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class MutableRemove<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V>& RemoveInPlace(const K& key, MutableMap<K, V>& map) noexcept {
    return map.RemoveInPlace(key);
  }

  static MutableMap<K, V>& RemoveInPlace(const MutableMap<K, V>& source, MutableMap<K, V>& map) noexcept {
    return map.RemoveInPlace(source);
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  static MutableMap<K, V>& RemoveInPlace(const U& source, MutableMap<K, V>& map) noexcept {
    return map.RemoveInPlace(source);
  }

};

}