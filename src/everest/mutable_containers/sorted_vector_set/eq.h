#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template<class T>
class Eq<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableSortedVectorSet<T>& lhs, const MutableSortedVectorSet<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}