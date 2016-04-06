#pragma once

#include <stddef.h>
#include <everest/containers/vector.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template <class T>
class Foldable<Vector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const Vector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, pointer[i]);
    }
    return memo;
  }

  template <class Fn,
            class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const Vector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const Vector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = length - 1; i; i--) {
      memo = f(memo, pointer[i]);
    }
    if (length > 0) {
      memo = f(memo, pointer[0]);
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const Vector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = vector.Pointer();
    auto length  = vector.Length();
    for (size_t i = 0; i < length; i++) {
      memo = f(memo, pointer[i]);
    }
    return memo;
  }

};

}