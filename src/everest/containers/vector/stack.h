#pragma once

#include <everest/containers/option.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/stack.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Stack<Vector<T>> {
public:

  static constexpr bool exists = true;

  static Vector<T> Push(const T& item, const Vector<T>& vector) noexcept {
    return Vector<T>(Stack<MutableVector<T>>::Push(item, vector));
  }

  static Vector<T> Pop(const Vector<T>& vector) noexcept {
    return Vector<T>(Stack<MutableVector<T>>::Pop(vector));
  }

  static Option<const T&> Top(const Vector<T>& vector) noexcept {
    return Stack<MutableVector<T>>::Top(vector);
  }

};

}