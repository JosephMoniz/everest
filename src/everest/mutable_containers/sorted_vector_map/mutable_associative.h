#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/mutable/mutable_associative.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class MutableAssociative<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorMap<K, V>& PutInPlace(K&& key, V&& value,
                                                  MutableSortedVectorMap<K, V>& container) noexcept
  {
    return container.PutInPlace(std::move(key), std::move(value));
  }

  static MutableSortedVectorMap<K, V>& PutInPlace(MutableSortedVectorMap<K, V>&& source,
                                                  MutableSortedVectorMap<K, V>& container) noexcept
  {
    return container.PutInPlace(std::move(source));
  }

  static V* GetInPlace(const K& key, MutableSortedVectorMap<K, V>& container) noexcept {
    return container.GetInPlace(key);
  };

};


}