#pragma once

#include <everest/containers/mutable/mutable_vector.h>
#include <everest/traits/lawful/foldable.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Foldable<MutableVector<T>> {
public:

  static constexpr bool exists = true;

  static constexpr T Fold(const MutableVector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, pointer[i]);
    }
    return memo;
  }

  template <class Fn,
    class M = typename std::result_of<Fn(T)>::type>
  static constexpr M FoldMap(Fn f, const MutableVector<T>& vector) noexcept {
    auto memo    = ZeroVal<T>::Zero();
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      memo = Semigroup<T>::Add(memo, f(pointer[i]));
    }
    return memo;
  }

  template <class Fn, class B>
  static constexpr B FoldR(Fn f,
                           const B& init,
                           const MutableVector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    if (length == 0) {
      return init;
    } else {
      for (size_t i = length - 1; i; i--) {
        memo = f(memo, pointer[i]);
      }
      if (length > 0) {
        memo = f(memo, pointer[0]);
      }
      return memo;
    }
  }

  template <class Fn, class B>
  static constexpr B FoldL(Fn f,
                           const B& init,
                           const MutableVector<T>& vector) noexcept
  {
    auto memo    = init;
    auto pointer = Pointer(vector);
    auto length  = Length(vector);
    for (size_t i = 0; i < length; i++) {
      memo = f(memo, pointer[i]);
    }
    return memo;
  }

};

}