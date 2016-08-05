#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template <class K, class V>
class Shows<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableSortedVectorMap<K, V>& map) noexcept {
    return map.Show();
  }

};

}