#pragma once

#include <everest/mutable_containers/mutable_vector.h>
#include <everest/traits/unlawful/stack.h>

namespace everest {

template<class T>
class MutableVector;

template <class T>
class Stack<MutableVector<T>> final {
public:

  static constexpr bool exists = true;

  static MutableVector<T> Push(const T& item, const MutableVector<T>& vector) noexcept {
    return vector.Push(item);
  }

  static MutableVector<T> Pop(const MutableVector<T>& vector) noexcept {
    return vector.Pop();
  }

  static Option<const T&> Top(const MutableVector<T>& vector) noexcept {
    return vector.At(Length(vector) - 1);
  }

};

}