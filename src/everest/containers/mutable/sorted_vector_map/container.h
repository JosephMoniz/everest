#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_map.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class K, class V>
class MutableSortedVectorMap;

template <class K, class V>
class Container<MutableSortedVectorMap<K, V>> final {
public:

static constexpr bool exists = true;

  static size_t Length(const MutableSortedVectorMap<K, V>& map) noexcept {
    return map.Length();
  }

  static bool IsEmpty(const MutableSortedVectorMap<K, V>& map) noexcept {
    return map.IsEmpty();
  }

};

}