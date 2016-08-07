#pragma once

#include <everest/containers/option.h>
#include <everest/containers/vector.h>
#include <everest/traits/unlawful/stack.h>

namespace everest {

template<class T>
class Vector;

template <class T>
class Stack<Vector<T>> final {
public:

  static constexpr bool exists = true;

  static Vector<T> Push(const T& item, const Vector<T>& vector) noexcept {
    return vector.Push(item);
  }

  static Vector<T> Pop(const Vector<T>& vector) noexcept {
    return vector.Pop();
  }

  static Option<const T&> Top(const Vector<T>& vector) noexcept {
    return vector.Top();
  }

};

}