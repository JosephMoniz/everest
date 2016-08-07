#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class Containable<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static bool Contains(const K& key, const MutableSortedVectorMap<K, V>& map) noexcept {
    return map.Contains(key);
  }

};

}