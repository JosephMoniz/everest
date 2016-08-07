#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template<class T>
class Semigroup<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorSet<T> Add(const MutableSortedVectorSet<T>& lhs,
                                       const MutableSortedVectorSet<T>& rhs) noexcept
  {
    return lhs.Add(rhs);
  }

};

}