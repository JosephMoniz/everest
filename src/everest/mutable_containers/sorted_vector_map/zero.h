#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class ZeroVal<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorMap<K, V> Zero() noexcept {
    return MutableSortedVectorMap<K, V>::Zero();
  }

};

}