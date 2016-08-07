#pragma once

#include <everest/mutable_containers/mutable_map.h>
#include <everest/traits/unlawful/associative.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Associative<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V> Put(K&& key, V&& value, MutableMap<K, V>& container) noexcept {
    return container.Put(std::move(key), std::move(value));
  }

  static MutableMap<K, V> Put(MutableMap<K, V>&& source, MutableMap<K, V>& container) noexcept {
    return container.Put(std::move(source));
  }

  static const V* Get(const K& key, MutableMap<K, V>& container) noexcept {
    return container.Get(key);
  };

};

}