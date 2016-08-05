#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/unlawful/mutable/mutable_associative.h>
#include <everest/traits/unlawful/mutable/mutable_find.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class MutableAssociative<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableMap<K, V>& PutInPlace(K&& key, V&& value, MutableMap<K, V>& container) noexcept {
    return container.PutInPlace(std::move(key), std::move(value));
  }

  static MutableMap<K, V>& PutInPlace(MutableMap<K, V>&& source, MutableMap<K, V>& container) noexcept {
    return container.PutInPlace(std::move(source));
  }

  static V* GetInPlace(const K& key, MutableMap<K, V>& container) noexcept {
    return container.GetInPlace(key);
  };

};

}