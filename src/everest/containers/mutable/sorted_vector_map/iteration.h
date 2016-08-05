#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template <class K, class V>
class Iteration<MutableSortedVectorMap<K, V>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableSortedVectorMap<K, V>& container, F function) noexcept {
    container.ForEach(function);
  }

};

}