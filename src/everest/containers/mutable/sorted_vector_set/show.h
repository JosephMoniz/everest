#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class Shows<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableSortedVectorSet<T>& set) noexcept {
    return set.Show();
  }

};

}