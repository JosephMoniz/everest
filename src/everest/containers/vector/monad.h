#pragma once

#include <everest/containers/vector.h>
#include <everest/traits/lawful/monad.h>

namespace everest {

template<class T>
class Monad<Vector<T>> {
public:

  static constexpr bool exists = true;

  template<class F, class B = nth_arg<typename std::result_of<F(T)>::type, 0>>
  static constexpr Vector<B> FlatMap(F f, const Vector<T>& vector) noexcept {
    auto results = MutableVector<T>();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (auto i = 0; i < length; i++) {
      auto expanded = f(pointer[i]);
      auto ePointer = expanded.Pointer();
      auto eLength  = expanded.Length();
      for (auto j = 0; j < eLength; j++) {
        results.Push(ePointer[j]);
      }
    }
    return Vector<T>(std::move(results));
  }

  template <class B>
  static constexpr Vector<B> Then(const Vector<T>& first, const Vector<B>& second) noexcept {
    return second;
  }

};

}