#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class MutableRemove<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorMap<K, V>& RemoveInPlace(const K& key, MutableSortedVectorMap<K, V>& map) noexcept {
    return map.RemoveInPlace(key);
  }

  static MutableSortedVectorMap<K, V>& RemoveInPlace(const MutableSortedVectorMap<K, V>& source,
                                                     MutableSortedVectorMap<K, V>& map) noexcept
  {
    return map.RemoveInPlace(source);
  }

  template<class U, class = std::enable_if<Iteration<U>::exists>>
  static MutableSortedVectorMap<K, V>& RemoveInPlace(const U& source, MutableSortedVectorMap<K, V>& map) noexcept {
    return map.RemoveInPlace(source);
  }

};

}