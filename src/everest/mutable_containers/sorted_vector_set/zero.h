#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template<class T>
class ZeroVal<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  static MutableSortedVectorSet<T> Zero() noexcept {
    return MutableSortedVectorSet<T>::Zero();
  }

};

}