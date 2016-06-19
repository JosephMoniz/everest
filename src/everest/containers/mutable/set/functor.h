#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/lawful/functor.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Functor<MutableSet<T>> {
public:

  static constexpr bool exists = true;

  template <class F, class B = typename std::result_of<F(T)>::type>
  static MutableSet<B> Map(F f, const MutableSet<T>& set) noexcept {
    auto result = MutableSet<B>();
    ForEach(set, [&](const T& item) {
      AddInPlace(f(item), result);
    });
    return result;
  }

};

}