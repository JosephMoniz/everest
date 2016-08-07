#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/associative.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class Associative<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorMap<K, V> Put(K&& key, V&& value, MutableSortedVectorMap<K, V>& container) noexcept {
    return container.Put(std::move(key), std::move(value));
  }

  static MutableSortedVectorMap<K, V> Put(MutableSortedVectorMap<K, V>&& source,
                                          MutableSortedVectorMap<K, V>& container) noexcept
  {
    return container.Put(std::move(source));
  }

  static const V* Get(const K& key, MutableSortedVectorMap<K, V>& container) noexcept {
    return container.Get(key);
  };

};

}