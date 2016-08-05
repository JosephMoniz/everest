#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template<class K, class V>
class Copyable<MutableSortedVectorMap<K, V>> final {
public:

static constexpr bool exists = true;

  static MutableSortedVectorMap<K, V> Copy(const MutableSortedVectorMap<K, V>& map) noexcept {
    return map.Copy();
  }

};

}