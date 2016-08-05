#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class Eq<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableSortedVectorMap<K, V>& lhs, const MutableSortedVectorMap<K, V>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}