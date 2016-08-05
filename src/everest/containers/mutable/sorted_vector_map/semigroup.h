#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_map.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class Semigroup<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorMap<K, V> Add(const MutableSortedVectorMap<K, V>& lhs,
                                          const MutableSortedVectorMap<K, V>& rhs) noexcept
  {
    return lhs.Add(rhs);
  }

};

}