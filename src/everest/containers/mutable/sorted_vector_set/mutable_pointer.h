#pragma once

#include <everest/containers/mutable/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template<class T>
class MutablePointable<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static T* Pointer(MutableSortedVectorSet<T>& set) noexcept {
    return set.MutablePointer();
  }

};

}