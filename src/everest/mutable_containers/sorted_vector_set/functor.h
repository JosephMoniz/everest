#pragma once

#include <everest/mutable_containers/mutable_sorted_vector_set.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template <class T>
class MutableSortedVectorSet;

template <class T>
class Functor<MutableSortedVectorSet<T>> final {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableSortedVectorSet<B> Map(F f, const MutableSortedVectorSet<T>& set) noexcept {
    return set.Map(f);
  }

};

}