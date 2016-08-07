#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class Iteration<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableSortedVectorSet<T>& set, const F& function) noexcept {
    set.ForEach(function);
  }

};

}