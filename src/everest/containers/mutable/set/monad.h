#pragma once

#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template<class T>
class MutableSet;

template<class T>
class Monad<MutableSet<T>> final {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr MutableSet<B> FlatMap(F f, const MutableSet<T>& set) noexcept {
    auto results = MutableSet<T>();
    ForEach(set, [&](const T& item) {
      ForEach(f(item), [&](const T& inner) {
        AddInPlace(inner, results);
      });
    });
    return results;
  }

  template <class B>
  static constexpr MutableSet<B> Then(const MutableSet<T>& first, const MutableSet<B>& second) noexcept {
    return second;
  }

};

}